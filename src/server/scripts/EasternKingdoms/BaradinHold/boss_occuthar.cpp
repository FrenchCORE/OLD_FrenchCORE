/*
 * Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
 *
 * Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2012 - 2012 FrenchCORE <http://www.frcore.com/>
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

#include "ScriptPCH.h"
#include "baradin_hold.h"

class boss_occuthar : public CreatureScript
{
public:
    boss_occuthar() : CreatureScript("boss_occuthar") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_occutharAI (creature);
    }

    struct boss_occutharAI : public ScriptedAI
    {
        boss_occutharAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        void Reset() {}

        void EnterCombat(Unit* /*pWho*/) {}

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_occuthar()
{
    new boss_occuthar();
}