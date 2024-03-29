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
 SDName: Instance_Blackrock_Depths
 SD%Complete: 100
 SDComment:
 SDCategory: Blackrock Depths
 EndScriptData */

#include "ScriptPCH.h"
#include "blackrock_depths.h"

#define TIMER_TOMBOFTHESEVEN    15000

enum eEnums {
	MAX_ENCOUNTER = 6,

	NPC_EMPEROR = 9019,
	NPC_PHALANX = 9502,
	NPC_ANGERREL = 9035,
	NPC_DOPEREL = 9040,
	NPC_HATEREL = 9034,
	NPC_VILEREL = 9036,
	NPC_SEETHREL = 9038,
	NPC_GLOOMREL = 9037,
	NPC_DOOMREL = 9039,
	NPC_MAGMUS = 9938,

	GO_ARENA1 = 161525,
	GO_ARENA2 = 161522,
	GO_ARENA3 = 161524,
	GO_ARENA4 = 161523,
	GO_SHADOW_LOCK = 161460,
	GO_SHADOW_MECHANISM = 161461,
	GO_SHADOW_GIANT_DOOR = 157923,
	GO_SHADOW_DUMMY = 161516,
	GO_BAR_KEG_SHOT = 170607,
	GO_BAR_KEG_TRAP = 171941,
	GO_BAR_DOOR = 170571,
	GO_TOMB_ENTER = 170576,
	GO_TOMB_EXIT = 170577,
	GO_LYCEUM = 170558,
	GO_SF_N = 174745, // Shadowforge Brazier North
	GO_SF_S = 174744, // Shadowforge Brazier South
	GO_GOLEM_ROOM_N = 170573, // Magmus door North
	GO_GOLEM_ROOM_S = 170574, // Magmus door Soutsh
	GO_THRONE_ROOM = 170575, // Throne door

	GO_SPECTRAL_CHALICE = 164869,
	GO_CHEST_SEVEN = 169243
};

class instance_blackrock_depths: public InstanceMapScript {
public:
	instance_blackrock_depths() :
			InstanceMapScript("instance_blackrock_depths", 230) {
	}

	InstanceScript* GetInstanceScript(InstanceMap* pMap) const {
		return new instance_blackrock_depths_InstanceMapScript(pMap);
	}

	struct instance_blackrock_depths_InstanceMapScript: public InstanceScript {
		instance_blackrock_depths_InstanceMapScript(Map* pMap) :
				InstanceScript(pMap) {
			Initialize();
		}
		;

		uint32 m_auiEncounter[MAX_ENCOUNTER];
		std::string str_data;

		uint64 EmperorGUID;
		uint64 PhalanxGUID;
		uint64 MagmusGUID;

		uint64 GoArena1GUID;
		uint64 GoArena2GUID;
		uint64 GoArena3GUID;
		uint64 GoArena4GUID;
		uint64 GoShadowLockGUID;
		uint64 GoShadowMechGUID;
		uint64 GoShadowGiantGUID;
		uint64 GoShadowDummyGUID;
		uint64 GoBarKegGUID;
		uint64 GoBarKegTrapGUID;
		uint64 GoBarDoorGUID;
		uint64 GoTombEnterGUID;
		uint64 GoTombExitGUID;
		uint64 GoLyceumGUID;
		uint64 GoSFSGUID;
		uint64 GoSFNGUID;
		uint64 GoGolemNGUID;
		uint64 GoGolemSGUID;
		uint64 GoThroneGUID;
		uint64 GoChestGUID;
		uint64 GoSpectralChaliceGUID;

		uint32 BarAleCount;
		uint32 GhostKillCount;
		uint64 TombBossGUIDs[7];
		uint64 TombEventStarterGUID;
		uint32 TombTimer;
		uint32 TombEventCounter;

		void Initialize() {
			memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

			EmperorGUID = 0;
			PhalanxGUID = 0;
			MagmusGUID = 0;

			GoArena1GUID = 0;
			GoArena2GUID = 0;
			GoArena3GUID = 0;
			GoArena4GUID = 0;
			GoShadowLockGUID = 0;
			GoShadowMechGUID = 0;
			GoShadowGiantGUID = 0;
			GoShadowDummyGUID = 0;
			GoBarKegGUID = 0;
			GoBarKegTrapGUID = 0;
			GoBarDoorGUID = 0;
			GoTombEnterGUID = 0;
			GoTombExitGUID = 0;
			GoLyceumGUID = 0;
			GoSFSGUID = 0;
			GoSFNGUID = 0;
			GoGolemNGUID = 0;
			GoGolemSGUID = 0;
			GoThroneGUID = 0;
			GoChestGUID = 0;
			GoSpectralChaliceGUID = 0;

			BarAleCount = 0;
			GhostKillCount = 0;
			TombEventStarterGUID = 0;
			TombTimer = TIMER_TOMBOFTHESEVEN;
			TombEventCounter = 0;

			for (uint8 i = 0; i < 7; ++i)
				TombBossGUIDs[i] = 0;
		}

		void OnCreatureCreate(Creature* pCreature, bool /*add*/) {
			switch (pCreature->GetEntry()) {
			case NPC_EMPEROR:
				EmperorGUID = pCreature->GetGUID();
				break;
			case NPC_PHALANX:
				PhalanxGUID = pCreature->GetGUID();
				break;
			case NPC_DOOMREL:
				TombBossGUIDs[0] = pCreature->GetGUID();
				break;
			case NPC_DOPEREL:
				TombBossGUIDs[1] = pCreature->GetGUID();
				break;
			case NPC_HATEREL:
				TombBossGUIDs[2] = pCreature->GetGUID();
				break;
			case NPC_VILEREL:
				TombBossGUIDs[3] = pCreature->GetGUID();
				break;
			case NPC_SEETHREL:
				TombBossGUIDs[4] = pCreature->GetGUID();
				break;
			case NPC_GLOOMREL:
				TombBossGUIDs[5] = pCreature->GetGUID();
				break;
			case NPC_ANGERREL:
				TombBossGUIDs[6] = pCreature->GetGUID();
				break;
			case NPC_MAGMUS:
				MagmusGUID = pCreature->GetGUID();
				if (!pCreature->isAlive())
					HandleGameObject(GetData64(DATA_THRONE_DOOR), true); // if Magmus is dead open door to last boss
				break;
			}
		}

		void OnGameObjectCreate(GameObject* pGo, bool /*add*/) {
			switch (pGo->GetEntry()) {
			case GO_ARENA1:
				GoArena1GUID = pGo->GetGUID();
				break;
			case GO_ARENA2:
				GoArena2GUID = pGo->GetGUID();
				break;
			case GO_ARENA3:
				GoArena3GUID = pGo->GetGUID();
				break;
			case GO_ARENA4:
				GoArena4GUID = pGo->GetGUID();
				break;
			case GO_SHADOW_LOCK:
				GoShadowLockGUID = pGo->GetGUID();
				break;
			case GO_SHADOW_MECHANISM:
				GoShadowMechGUID = pGo->GetGUID();
				break;
			case GO_SHADOW_GIANT_DOOR:
				GoShadowGiantGUID = pGo->GetGUID();
				break;
			case GO_SHADOW_DUMMY:
				GoShadowDummyGUID = pGo->GetGUID();
				break;
			case GO_BAR_KEG_SHOT:
				GoBarKegGUID = pGo->GetGUID();
				break;
			case GO_BAR_KEG_TRAP:
				GoBarKegTrapGUID = pGo->GetGUID();
				break;
			case GO_BAR_DOOR:
				GoBarDoorGUID = pGo->GetGUID();
				break;
			case GO_TOMB_ENTER:
				GoTombEnterGUID = pGo->GetGUID();
				break;
			case GO_TOMB_EXIT:
				GoTombExitGUID = pGo->GetGUID();
				if (GhostKillCount >= 7)
					HandleGameObject(0, true, pGo);
				else
					HandleGameObject(0, false, pGo);
				break;
			case GO_LYCEUM:
				GoLyceumGUID = pGo->GetGUID();
				break;
			case GO_SF_S:
				GoSFSGUID = pGo->GetGUID();
				break;
			case GO_SF_N:
				GoSFNGUID = pGo->GetGUID();
				break;
			case GO_GOLEM_ROOM_N:
				GoGolemNGUID = pGo->GetGUID();
				break;
			case GO_GOLEM_ROOM_S:
				GoGolemSGUID = pGo->GetGUID();
				break;
			case GO_THRONE_ROOM:
				GoThroneGUID = pGo->GetGUID();
				break;
			case GO_CHEST_SEVEN:
				GoChestGUID = pGo->GetGUID();
				break;
			case GO_SPECTRAL_CHALICE:
				GoSpectralChaliceGUID = pGo->GetGUID();
				break;
			}
		}

		void SetData64(uint32 type, uint64 data) {
			sLog->outDebug(
					LOG_FILTER_TSCR,
					"TSCR: Instance Blackrock Depths: SetData64 update (Type: %u Data " UI64FMTD ")",
					type, data);

			switch (type) {
			case DATA_EVENSTARTER:
				TombEventStarterGUID = data;
				if (!TombEventStarterGUID)
					TombOfSevenReset(); //reset
				else
					TombOfSevenStart(); //start
				break;
			}
		}

		void SetData(uint32 type, uint32 data) {
			sLog->outDebug(
					LOG_FILTER_TSCR,
					"TSCR: Instance Blackrock Depths: SetData update (Type: %u Data %u)",
					type, data);

			switch (type) {
			case TYPE_RING_OF_LAW:
				m_auiEncounter[0] = data;
				break;
			case TYPE_VAULT:
				m_auiEncounter[1] = data;
				break;
			case TYPE_BAR:
				if (data == SPECIAL)
					++BarAleCount;
				else
					m_auiEncounter[2] = data;
				break;
			case TYPE_TOMB_OF_SEVEN:
				m_auiEncounter[3] = data;
				break;
			case TYPE_LYCEUM:
				m_auiEncounter[4] = data;
				break;
			case TYPE_IRON_HALL:
				m_auiEncounter[5] = data;
				break;
			case DATA_GHOSTKILL:
				GhostKillCount += data;
				break;
			}

			if (data == DONE || GhostKillCount >= 7) {
				OUT_SAVE_INST_DATA;

				std::ostringstream saveStream;
				saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1]
						<< " " << m_auiEncounter[2] << " " << m_auiEncounter[3]
						<< " " << m_auiEncounter[4] << " " << m_auiEncounter[5]
						<< " " << GhostKillCount;

				str_data = saveStream.str();

				SaveToDB();
				OUT_SAVE_INST_DATA_COMPLETE;
			}
		}

		uint32 GetData(uint32 type) {
			switch (type) {
			case TYPE_RING_OF_LAW:
				return m_auiEncounter[0];
			case TYPE_VAULT:
				return m_auiEncounter[1];
			case TYPE_BAR:
				if (m_auiEncounter[2] == IN_PROGRESS && BarAleCount == 3)
					return SPECIAL;
				else
					return m_auiEncounter[2];
			case TYPE_TOMB_OF_SEVEN:
				return m_auiEncounter[3];
			case TYPE_LYCEUM:
				return m_auiEncounter[4];
			case TYPE_IRON_HALL:
				return m_auiEncounter[5];
			case DATA_GHOSTKILL:
				return GhostKillCount;
			}
			return 0;
		}

		uint64 GetData64(uint32 data) {
			switch (data) {
			case DATA_EMPEROR:
				return EmperorGUID;
			case DATA_PHALANX:
				return PhalanxGUID;
			case DATA_ARENA1:
				return GoArena1GUID;
			case DATA_ARENA2:
				return GoArena2GUID;
			case DATA_ARENA3:
				return GoArena3GUID;
			case DATA_ARENA4:
				return GoArena4GUID;
			case DATA_GO_BAR_KEG:
				return GoBarKegGUID;
			case DATA_GO_BAR_KEG_TRAP:
				return GoBarKegTrapGUID;
			case DATA_GO_BAR_DOOR:
				return GoBarDoorGUID;
			case DATA_EVENSTARTER:
				return TombEventStarterGUID;
			case DATA_SF_BRAZIER_N:
				return GoSFNGUID;
			case DATA_SF_BRAZIER_S:
				return GoSFSGUID;
			case DATA_THRONE_DOOR:
				return GoThroneGUID;
			case DATA_GOLEM_DOOR_N:
				return GoGolemNGUID;
			case DATA_GOLEM_DOOR_S:
				return GoGolemSGUID;
			case DATA_GO_CHALICE:
				return GoSpectralChaliceGUID;
			}
			return 0;
		}

		std::string GetSaveData() {
			return str_data;
		}

		void Load(const char* in) {
			if (!in) {
				OUT_LOAD_INST_DATA_FAIL;
				return;
			}

			OUT_LOAD_INST_DATA(in);

			std::istringstream loadStream(in);
			loadStream >> m_auiEncounter[0] >> m_auiEncounter[1]
					>> m_auiEncounter[2] >> m_auiEncounter[3]
					>> m_auiEncounter[4] >> m_auiEncounter[5] >> GhostKillCount;

			for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
				if (m_auiEncounter[i] == IN_PROGRESS)
					m_auiEncounter[i] = NOT_STARTED;
			if (GhostKillCount > 0 && GhostKillCount < 7)
				GhostKillCount = 0; //reset tomb of seven event
			if (GhostKillCount >= 7)
				GhostKillCount = 7;

			OUT_LOAD_INST_DATA_COMPLETE;
		}

		void TombOfSevenEvent() {
			if (GhostKillCount < 7 && TombBossGUIDs[TombEventCounter]) {
				if (Creature* boss = instance->GetCreature(TombBossGUIDs[TombEventCounter])) {
					boss->setFaction(FACTION_HOSTILE);
					boss->RemoveFlag(UNIT_FIELD_FLAGS,
							UNIT_FLAG_OOC_NOT_ATTACKABLE);
					if (Unit *pTarget = boss->SelectNearestTarget(500))
						boss->AI()->AttackStart(pTarget);
				}
			}
		}

		void TombOfSevenReset() {
			HandleGameObject(GoTombExitGUID, false); //event reseted, close exit door
			HandleGameObject(GoTombEnterGUID, true); //event reseted, open entrance door
			for (uint8 i = 0; i < 7; ++i) {
				if (Creature* boss = instance->GetCreature(TombBossGUIDs[i])) {
					if (!boss->isAlive()) { //do not call EnterEvadeMode(), it will create infinit loops
						boss->Respawn();
						boss->RemoveAllAuras();
						boss->DeleteThreatList();
						boss->CombatStop(true);
						boss->LoadCreaturesAddon();
						boss->GetMotionMaster()->MoveTargetedHome();
						boss->SetLootRecipient(NULL);
					}
					boss->setFaction(FACTION_FRIEND);
				}
			}
			GhostKillCount = 0;
			TombEventStarterGUID = 0;
			TombEventCounter = 0;
			TombTimer = TIMER_TOMBOFTHESEVEN;
			SetData(TYPE_TOMB_OF_SEVEN, NOT_STARTED);
		}

		void TombOfSevenStart() {
			HandleGameObject(GoTombExitGUID, false); //event started, close exit door
			HandleGameObject(GoTombEnterGUID, false); //event started, close entrance door
			SetData(TYPE_TOMB_OF_SEVEN, IN_PROGRESS);
		}

		void TombOfSevenEnd() {
			DoRespawnGameObject(GoChestGUID, DAY);
			HandleGameObject(GoTombExitGUID, true); //event done, open exit door
			HandleGameObject(GoTombEnterGUID, true); //event done, open entrance door
			TombEventStarterGUID = 0;
			SetData(TYPE_TOMB_OF_SEVEN, DONE);
		}
		void Update(uint32 diff) {
			if (TombEventStarterGUID && GhostKillCount < 7) {
				if (TombTimer <= diff) {
					TombTimer = TIMER_TOMBOFTHESEVEN;
					++TombEventCounter;
					TombOfSevenEvent();
					// Check Killed bosses
					for (uint8 i = 0; i < 7; ++i) {
						if (Creature* boss = instance->GetCreature(TombBossGUIDs[i])) {
							if (!boss->isAlive()) {
								GhostKillCount = i + 1;
							}
						}
					}
				} else
					TombTimer -= diff;
			}
			if (GhostKillCount >= 7 && TombEventStarterGUID)
				TombOfSevenEnd();
		}
	};
};

void AddSC_instance_blackrock_depths() {
	new instance_blackrock_depths();
}
