/*
 * Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
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

/* ScriptData
 SDName: Boss_Illucia_Barov
 SD%Complete: 100
 SDComment:
 SDCategory: Scholomance
 EndScriptData */

#include "ScriptPCH.h"
#include "scholomance.h"

#define SPELL_CURSEOFAGONY      18671
#define SPELL_SHADOWSHOCK       20603
#define SPELL_SILENCE           15487
#define SPELL_FEAR              6215

class boss_illucia_barov: public CreatureScript {
public:
	boss_illucia_barov() :
			CreatureScript("boss_illucia_barov") {
	}

	CreatureAI* GetAI(Creature* pCreature) const {
		return new boss_illuciabarovAI(pCreature);
	}

	struct boss_illuciabarovAI: public ScriptedAI {
		boss_illuciabarovAI(Creature *c) :
				ScriptedAI(c) {
		}

		uint32 CurseOfAgony_Timer;
		uint32 ShadowShock_Timer;
		uint32 Silence_Timer;
		uint32 Fear_Timer;

		void Reset() {
			CurseOfAgony_Timer = 18000;
			ShadowShock_Timer = 9000;
			Silence_Timer = 5000;
			Fear_Timer = 30000;
		}

		void JustDied(Unit * /*killer*/) {
			InstanceScript *pInstance = me->GetInstanceScript();
			if (pInstance) {
				pInstance->SetData(DATA_LADYILLUCIABAROV_DEATH, 0);

				if (pInstance->GetData(TYPE_GANDLING) == IN_PROGRESS)
					me->SummonCreature(1853, 180.73f, -9.43856f, 75.507f,
							1.61399f, TEMPSUMMON_DEAD_DESPAWN, 0);
			}
		}

		void EnterCombat(Unit * /*who*/) {
		}

		void UpdateAI(const uint32 diff) {
			if (!UpdateVictim())
				return;

			//CurseOfAgony_Timer
			if (CurseOfAgony_Timer <= diff) {
				DoCast(me->getVictim(), SPELL_CURSEOFAGONY);
				CurseOfAgony_Timer = 30000;
			} else
				CurseOfAgony_Timer -= diff;

			//ShadowShock_Timer
			if (ShadowShock_Timer <= diff) {
				Unit *pTarget = NULL;
				pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);
				if (pTarget)
					DoCast(pTarget, SPELL_SHADOWSHOCK);

				ShadowShock_Timer = 12000;
			} else
				ShadowShock_Timer -= diff;

			//Silence_Timer
			if (Silence_Timer <= diff) {
				DoCast(me->getVictim(), SPELL_SILENCE);
				Silence_Timer = 14000;
			} else
				Silence_Timer -= diff;

			//Fear_Timer
			if (Fear_Timer <= diff) {
				DoCast(me->getVictim(), SPELL_FEAR);
				Fear_Timer = 30000;
			} else
				Fear_Timer -= diff;

			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_boss_illuciabarov() {
	new boss_illucia_barov();
}
