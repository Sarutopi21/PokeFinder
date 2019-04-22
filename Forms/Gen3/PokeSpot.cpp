/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2019 by Admiral_Fish, bumba, and EzPzStreamz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <QSettings>
#include "PokeSpot.hpp"
#include "ui_PokeSpot.h"
#include <Core/Parents/FrameCompare.hpp>
#include <Core/RNG/LCRNG.hpp>
#include <Core/Util/Nature.hpp>

PokeSpot::PokeSpot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PokeSpot)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose);

    setupModels();
}

PokeSpot::~PokeSpot()
{
    QSettings setting;
    setting.setValue("pokespotTID", ui->textBoxTID->text());
    setting.setValue("pokespotSID", ui->textBoxSID->text());

    delete ui;
}

void PokeSpot::setupModels()
{
    model = new PokeSpotModel(ui->tableView);

    ui->textBoxSeed->setValues(InputType::Seed32Bit);
    ui->textBoxStartingFrame->setValues(InputType::Frame32Bit);
    ui->textBoxMaxResults->setValues(InputType::Frame32Bit);
    ui->textBoxTID->setValues(InputType::TIDSID);
    ui->textBoxSID->setValues(InputType::TIDSID);

    ui->comboBoxGenderRatio->setItemData(0, 0);
    ui->comboBoxGenderRatio->setItemData(1, 127);
    ui->comboBoxGenderRatio->setItemData(2, 191);
    ui->comboBoxGenderRatio->setItemData(3, 63);
    ui->comboBoxGenderRatio->setItemData(4, 31);
    ui->comboBoxGenderRatio->setItemData(5, 1);
    ui->comboBoxGenderRatio->setItemData(6, 2);

    ui->tableView->setModel(model);

    ui->comboBoxNature->setup(Nature::getNatures());
    ui->comboBoxSpotType->setup();

    QSettings setting;
    if (setting.contains("pokespotTID")) ui->textBoxTID->setText(setting.value("pokespotTID").toString());
    if (setting.contains("pokespotSID")) ui->textBoxSID->setText(setting.value("pokespotSID").toString());
}

void PokeSpot::on_pushButtonGenerate_clicked()
{
    model->clearModel();

    QVector<Frame3> frames;

    u32 seed = ui->textBoxSeed->getUInt();
    u32 initialFrame = ui->textBoxStartingFrame->getUInt();
    u32 maxResults = ui->textBoxMaxResults->getUInt();
    u16 tid = ui->textBoxTID->getUShort();
    u16 sid = ui->textBoxSID->getUShort();
    u8 genderRatio = ui->comboBoxGenderRatio->currentData().toUInt();

    XDRNG rng(seed, initialFrame - 1);
    QVector<u16> rngList(maxResults + 5);
    for (u16 &x : rngList)
    {
        x = rng.nextUShort();
    }

    Frame3 frame = Frame3(tid, sid, tid ^ sid);
    FrameCompare compare = FrameCompare(ui->comboBoxGender->currentIndex(), ui->comboBoxAbility->currentIndex(),
                                        ui->comboBoxNature->getChecked(), ui->checkBoxShinyOnly->isChecked());

    QVector<bool> spots = ui->comboBoxSpotType->getChecked();

    for (u32 cnt = 0; cnt < maxResults; cnt++)
    {
        // Check if frame is a valid pokespot call
        if ((rngList.at(cnt) % 3) == 0)
        {
            // Munchlax provides a frame skip
            if ((rngList.at(cnt + 1) % 100) >= 10)
            {
                // Check what type the pokespot is
                u8 call = rngList.at(cnt + 2) % 100;
                if (call < 50)
                {
                    if (!spots.at(0))
                    {
                        continue;
                    }
                    frame.setLockReason(tr("Common"));
                }
                else if (call > 49 && call < 85)
                {
                    if (!spots.at(1))
                    {
                        continue;
                    }
                    frame.setLockReason(tr("Uncommon"));
                }
                else
                {
                    if (!spots.at(2))
                    {
                        continue;
                    }
                    frame.setLockReason(tr("Rare"));
                }

                frame.setPID(rngList.at(cnt + 4), rngList.at(cnt + 3), genderRatio);
                if (compare.comparePID(frame))
                {
                    frame.setFrame(cnt + initialFrame);
                    frames.append(frame);
                }
            }
        }
    }

    model->addItems(frames);
}

void PokeSpot::on_pushButtonAnyAbility_clicked()
{
    ui->comboBoxAbility->setCurrentIndex(0);
}
