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

#ifndef DEF_BFD_H
#define DEF_BFD_H

enum Data64 {
	DATA_SHRINE1,
	DATA_SHRINE2,
	DATA_SHRINE3,
	DATA_SHRINE4,
	DATA_TWILIGHT_LORD_KELRIS,
	DATA_SHRINE_OF_GELIHAST,
	DATA_ALTAR_OF_THE_DEEPS,
	DATA_MAINDOOR,
};

enum Data {
	TYPE_GELIHAST, TYPE_KELRIS, TYPE_SHRINE, TYPE_AKU_MAI, DATA_FIRE, DATA_EVENT
};

enum Creatures {
	NPC_TWILIGHT_LORD_KELRIS = 4832,
	NPC_LORGUS_JETT = 12902,

	NPC_AKU_MAI_SNAPJAW = 4825,
	NPC_MURKSHALLOW_SOFTSHELL = 4977,
	NPC_AKU_MAI_SERVANT = 4978,
	NPC_BARBED_CRUSTACEAN = 4823,

	NPC_MORRIDUNE = 6729
};

enum GameObjects {
	GO_SHRINE_OF_GELIHAST = 103015,
	GO_FIRE_OF_AKU_MAI_1 = 21118,
	GO_FIRE_OF_AKU_MAI_2 = 21119,
	GO_FIRE_OF_AKU_MAI_3 = 21120,
	GO_FIRE_OF_AKU_MAI_4 = 21121,
	GO_AKU_MAI_DOOR = 21117,
	GO_ALTAR_OF_THE_DEEPS = 103016
};
#endif
