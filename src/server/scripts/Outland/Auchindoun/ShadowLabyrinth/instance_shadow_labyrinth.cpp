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
SDName: Instance_Shadow_Labyrinth
SD%Complete: 85
SDComment: Some cleanup left along with save
SDCategory: Auchindoun, Shadow Labyrinth
EndScriptData */

#include "ScriptPCH.h"
#include "shadow_labyrinth.h"

#define MAX_ENCOUNTER 5

#define REFECTORY_DOOR          183296                      //door opened when blackheart the inciter dies
#define SCREAMING_HALL_DOOR     183295                      //door opened when grandmaster vorpil dies

/* Shadow Labyrinth encounters:
1 - Ambassador Hellmaw event
2 - Blackheart the Inciter event
3 - Grandmaster Vorpil event
4 - Murmur event
*/

class instance_shadow_labyrinth : public InstanceMapScript
{
public:
    instance_shadow_labyrinth() : InstanceMapScript("instance_shadow_labyrinth", 555) { }

    InstanceScript* GetInstanceScript(InstanceMap* pMap) const
    {
        return new instance_shadow_labyrinth_InstanceMapScript(pMap);
    }

    struct instance_shadow_labyrinth_InstanceMapScript : public InstanceScript
    {
        instance_shadow_labyrinth_InstanceMapScript(Map* pMap) : InstanceScript(pMap) {Initialize();};

        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string str_data;

        uint64 m_uiRefectoryDoorGUID;
        uint64 m_uiScreamingHallDoorGUID;

        uint64 m_uiGrandmasterVorpil;
        uint32 m_uiFelOverseerCount;

        void Initialize()
        {
            memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

            m_uiRefectoryDoorGUID = 0;
            m_uiScreamingHallDoorGUID = 0;

            m_uiGrandmasterVorpil = 0;
            m_uiFelOverseerCount = 0;
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (m_auiEncounter[i] == IN_PROGRESS) return true;

            return false;
        }

        void OnGameObjectCreate(GameObject* pGo, bool /*add*/)
        {
            switch(pGo->GetEntry())
            {
                case REFECTORY_DOOR:
                    m_uiRefectoryDoorGUID = pGo->GetGUID();
                    if (m_auiEncounter[2] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case SCREAMING_HALL_DOOR:
                    m_uiScreamingHallDoorGUID = pGo->GetGUID();
                    if (m_auiEncounter[3] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
            }
        }

        void OnCreatureCreate(Creature* pCreature, bool /*add*/)
        {
            switch(pCreature->GetEntry())
            {
                case 18732:
                    m_uiGrandmasterVorpil = pCreature->GetGUID();
                    break;
                case 18796:
                    if (pCreature->isAlive())
                    {
                        ++m_uiFelOverseerCount;
                        sLog->outDebug(LOG_FILTER_TSCR, "TSCR: Shadow Labyrinth: counting %u Fel Overseers.", m_uiFelOverseerCount);
                    }
                    break;
            }
        }

        void SetData(uint32 type, uint32 uiData)
        {
            switch(type)
            {
                case TYPE_HELLMAW:
                    m_auiEncounter[0] = uiData;
                    break;

                case TYPE_OVERSEER:
                    if (uiData != DONE)
                    {
                        sLog->outDebug(LOG_FILTER_TSCR, "TSCR: Shadow Labyrinth: TYPE_OVERSEER did not expect other data than DONE");
                        return;
                    }
                    if (m_uiFelOverseerCount)
                    {
                        --m_uiFelOverseerCount;

                        if (m_uiFelOverseerCount)
                            sLog->outDebug(LOG_FILTER_TSCR, "TSCR: Shadow Labyrinth: %u Fel Overseers left to kill.", m_uiFelOverseerCount);
                        else
                        {
                            m_auiEncounter[1] = DONE;
                            sLog->outDebug(LOG_FILTER_TSCR, "TSCR: Shadow Labyrinth: TYPE_OVERSEER == DONE");
                        }
                    }
                    break;

                case DATA_BLACKHEARTTHEINCITEREVENT:
                    if (uiData == DONE)
                        DoUseDoorOrButton(m_uiRefectoryDoorGUID);
                    m_auiEncounter[2] = uiData;
                    break;

                case DATA_GRANDMASTERVORPILEVENT:
                    if (uiData == DONE)
                        DoUseDoorOrButton(m_uiScreamingHallDoorGUID);
                    m_auiEncounter[3] = uiData;
                    break;

                case DATA_MURMUREVENT:
                    m_auiEncounter[4] = uiData;
                    break;
            }

            if (uiData == DONE)
            {
                if (type == TYPE_OVERSEER && m_uiFelOverseerCount != 0)
                    return;

                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " "
                    << m_auiEncounter[2] << " " << m_auiEncounter[3] << " " << m_auiEncounter[4];

                str_data = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        uint32 GetData(uint32 type)
        {
            switch(type)
            {
                case TYPE_HELLMAW: return m_auiEncounter[0];
                case TYPE_OVERSEER: return m_auiEncounter[1];
                case DATA_GRANDMASTERVORPILEVENT: return m_auiEncounter[3];
                case DATA_MURMUREVENT: return m_auiEncounter[4];
            }
            return false;
        }

        uint64 GetData64(uint32 identifier)
        {
            if (identifier == DATA_GRANDMASTERVORPIL)
                return m_uiGrandmasterVorpil;

            return 0;
        }

        std::string GetSaveData()
        {
            return str_data;
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            std::istringstream loadStream(in);
            loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3] >> m_auiEncounter[4];

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (m_auiEncounter[i] == IN_PROGRESS)
                    m_auiEncounter[i] = NOT_STARTED;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_shadow_labyrinth()
{
    new instance_shadow_labyrinth();
}