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
 SDName: Boss_Houndmaster_Loksey
 SD%Complete: 100
 SDComment:
 SDCategory: Scarlet Monastery
 EndScriptData */

#include "ScriptPCH.h"

enum eEnums {
	SAY_AGGRO = -1189021,
	SPELL_SUMMONSCARLETHOUND = 17164,
	SPELL_BLOODLUST = 6742
};

class boss_houndmaster_loksey: public CreatureScript {
public:
	boss_houndmaster_loksey() :
			CreatureScript("boss_houndmaster_loksey") {
	}

	CreatureAI* GetAI(Creature* pCreature) const {
		return new boss_houndmaster_lokseyAI(pCreature);
	}

	struct boss_houndmaster_lokseyAI: public ScriptedAI {
		boss_houndmaster_lokseyAI(Creature *c) :
				ScriptedAI(c) {
		}

		uint32 BloodLust_Timer;

		void Reset() {
			BloodLust_Timer = 20000;
		}

		void EnterCombat(Unit * /*who*/) {
			DoScriptText(SAY_AGGRO, me);
		}

		void UpdateAI(const uint32 diff) {
			if (!UpdateVictim())
				return;

			if (BloodLust_Timer <= diff) {
				DoCast(me, SPELL_BLOODLUST);
				BloodLust_Timer = 20000;
			} else
				BloodLust_Timer -= diff;

			DoMeleeAttackIfReady();
		}
	};
};

void AddSC_boss_houndmaster_loksey() {
	new boss_houndmaster_loksey();
}
