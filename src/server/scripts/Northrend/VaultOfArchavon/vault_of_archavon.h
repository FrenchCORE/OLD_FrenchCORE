/*
 * Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010 - 2012 FrenchCORE <http://www.frcore.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEF_ARCHAVON_H
#define DEF_ARCHAVON_H

enum Creatures
{
    CREATURE_ARCHAVON                           = 31125,
    CREATURE_EMALON                             = 33993,
    CREATURE_KORALON                            = 35013,
    CREATURE_TORAVON                            = 38433,
};

enum Data
{
    DATA_ARCHAVON   = 0,
    DATA_EMALON     = 1,
    DATA_KORALON    = 2,
    DATA_TORAVON    = 3,
};

#define MAX_ENCOUNTER 4

enum AchievementCriteriaIds
{
    CRITERIA_EARTH_WIND_FIRE_10 = 12018,
    CRITERIA_EARTH_WIND_FIRE_25 = 12019,
};

enum AchievementSpells
{
    SPELL_EARTH_WIND_FIRE_ACHIEVEMENT_CHECK = 68308,
};

#endif
