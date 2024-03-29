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

#ifndef OUTDOOR_PVP_SI_
#define OUTDOOR_PVP_SI_

#include "OutdoorPvP.h"

enum OutdoorPvPSISpells {
	SI_SILITHYST_FLAG_GO_SPELL = 29518,
	SI_SILITHYST_FLAG = 29519,
	SI_TRACES_OF_SILITHYST = 29534,
	SI_CENARION_FAVOR = 30754
};

const uint32 SI_MAX_RESOURCES = 200;

const uint8 OutdoorPvPSIBuffZonesNum = 3;

const uint32 OutdoorPvPSIBuffZones[OutdoorPvPSIBuffZonesNum] = { 1377, 3428,
		3429 };

const uint32 SI_AREATRIGGER_H = 4168;

const uint32 SI_AREATRIGGER_A = 4162;

const uint32 SI_TURNIN_QUEST_CM_A = 17090;

const uint32 SI_TURNIN_QUEST_CM_H = 18199;

const uint32 SI_SILITHYST_MOUND = 181597;

enum SI_WorldStates {
	SI_GATHERED_A = 2313, SI_GATHERED_H = 2314, SI_SILITHYST_MAX = 2317
};

class OutdoorPvPSI: public OutdoorPvP {
public:

	OutdoorPvPSI();

	bool SetupOutdoorPvP();

	void HandlePlayerEnterZone(Player *plr, uint32 zone);
	void HandlePlayerLeaveZone(Player *plr, uint32 zone);

	bool Update(uint32 diff);

	void FillInitialWorldStates(WorldPacket &data);

	void SendRemoveWorldStates(Player * plr);

	bool HandleAreaTrigger(Player * plr, uint32 trigger);

	bool HandleDropFlag(Player * plr, uint32 spellId);

	bool HandleCustomSpell(Player * plr, uint32 spellId, GameObject *go);

	void UpdateWorldState();

private:

	uint32 m_Gathered_A;
	uint32 m_Gathered_H;

	uint32 m_LastController;
};

#endif
