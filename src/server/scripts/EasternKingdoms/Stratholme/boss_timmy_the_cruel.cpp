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
 SDName: boss_timmy_the_cruel
 SD%Complete: 100
 SDComment:
 SDCategory: Stratholme
 EndScriptData */

#include "ScriptPCH.h"

#define SAY_SPAWN   "TIMMY!"

#define SPELL_RAVENOUSCLAW    17470

class boss_timmy_the_cruel: public CreatureScript {
public:
	boss_timmy_the_cruel() :
			CreatureScript("boss_timmy_the_cruel") {
	}

	CreatureAI* GetAI(Creature* pCreature) const {
		return new boss_timmy_the_cruelAI(pCreature);
	}

	struct boss_timmy_the_cruelAI: public ScriptedAI {
		boss_timmy_the_cruelAI(Creature *c) :
				ScriptedAI(c) {
		}

		uint32 RavenousClaw_Timer;
		bool HasYelled;

		void Reset() {
			RavenousClaw_Timer = 10000;
			HasYelled = false;
		}

		void EnterCombat(Unit * /*who*/) {
			if (!HasYelled) {
				me->MonsterYell(SAY_SPAWN, LANG_UNIVERSAL, NULL);
				HasYelled = true;
			}
		}

		void UpdateAI(const uint32 diff) {
			//Return since we have no target
			if (!UpdateVictim())
				return;

			//RavenousClaw
			if (RavenousClaw_Timer <= diff) {
				//Cast
				DoCast(me->getVictim(), SPELL_RAVENOUSCLAW);
				//15 seconds until we should cast this again
				RavenousClaw_Timer = 15000;
			} else
				RavenousClaw_Timer -= diff;

			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_boss_timmy_the_cruel() {
	new boss_timmy_the_cruel();
}
