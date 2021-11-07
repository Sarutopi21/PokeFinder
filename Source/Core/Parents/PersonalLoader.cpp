/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2021 by Admiral_Fish, bumba, and EzPzStreamz
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

#include "PersonalLoader.hpp"
#include <Core/Resources/Personal.hpp>

namespace PersonalLoader3
{
    const PersonalInfo *getPersonal()
    {
        return personal3.data();
    }
}

namespace PersonalLoader4
{
    const PersonalInfo *getPersonal()
    {
        return personal4.data();
    }
}

namespace PersonalLoader5
{
    const PersonalInfo *getPersonal()
    {
        return personal5.data();
    }
}

namespace PersonalLoader8
{
    const PersonalInfo *getPersonal()
    {
        return personal8.data();
    }

    PersonalInfo getPersonal(u16 species, u8 form)
    {
        PersonalInfo base = personal8[species];

        u16 formIndex = base.getFormStatIndex();

        if (form == 0 || formIndex == 0)
        {
            return base;
        }

        return personal8[formIndex + form - 1];
    }
}