/*
 * Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
 * 
 * Copyright (C) 2012 - 2012 FrenchCORE <http://www.frcore.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "gamePCH.h"
#include "LFGPlayerData.h"

LfgPlayerData::LfgPlayerData():
m_State(LFG_STATE_NONE), m_OldState(LFG_STATE_NONE), m_Roles(0), m_Comment("")
{}

LfgPlayerData::~LfgPlayerData()
{
}

void LfgPlayerData::SetState(LfgState state)
{
    switch(state)
    {
        case LFG_STATE_NONE:
        case LFG_STATE_DUNGEON:
        case LFG_STATE_FINISHED_DUNGEON:
            m_OldState = state;
                    // No break on purpose
        default:
            m_State = state;
        break;
    }
}

void LfgPlayerData::ClearState()
{
    m_SelectedDungeons.clear();
    m_Roles = 0;
    m_State = m_OldState;
}

void LfgPlayerData::SetLockedDungeons(const LfgLockMap& lockStatus)
{
    m_LockedDungeons = lockStatus;
}

void LfgPlayerData::SetRoles(uint8 roles)
{
    m_Roles = roles;
}

void LfgPlayerData::SetComment(const std::string& comment)
{
    m_Comment = comment;
}

void LfgPlayerData::SetSelectedDungeons(const LfgDungeonSet& dungeons)
{
    m_SelectedDungeons = dungeons;
}

void LfgPlayerData::ClearSelectedDungeons()
{
    m_SelectedDungeons.clear();
}

LfgState LfgPlayerData::GetState() const
{
    return m_State;
}

const LfgLockMap & LfgPlayerData::GetLockedDungeons() const
{
    return m_LockedDungeons;
}

uint8 LfgPlayerData::GetRoles() const
{
    return m_Roles;
}

const std::string& LfgPlayerData::GetComment() const
{
    return m_Comment;
}

const LfgDungeonSet& LfgPlayerData::GetSelectedDungeons() const
{
    return m_SelectedDungeons;
}
