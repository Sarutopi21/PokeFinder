/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2023 by Admiral_Fish, bumba, and EzPzStreamz
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

#include "StaticGenerator5.hpp"
#include <Core/Gen5/States/State5.hpp>

StaticGenerator5::StaticGenerator5(u32 initialAdvances, u32 maxAdvances, u32 delay, Method method, Lead lead,
                                   const StaticTemplate &staticTemplate, const Profile5 &profile, const StateFilter &filter) :
    StaticGenerator(initialAdvances, maxAdvances, delay, method, lead, staticTemplate, profile, filter)
{
}

std::vector<State5> StaticGenerator5::generate(u64 seed, u32 initialAdvances, u32 maxAdvances) const
{
    return std::vector<State5>();
}

std::vector<State5> StaticGenerator5::generate(u64 seed, const std::vector<std::pair<u32, std::array<u8, 6>>> &ivs) const
{
    return std::vector<State5>();
}
