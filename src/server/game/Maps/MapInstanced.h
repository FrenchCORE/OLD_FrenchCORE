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

#ifndef FRENCHCORE_MAP_INSTANCED_H
#define FRENCHCORE_MAP_INSTANCED_H

#include "Map.h"
#include "InstanceSaveMgr.h"
#include "DBCEnums.h"

class MapInstanced: public Map {
	friend class MapManager;
public:
	typedef UNORDERED_MAP< uint32, Map* > InstancedMaps;

	MapInstanced(uint32 id, time_t expiry);
	~MapInstanced() {}

	// functions overwrite Map versions
	void Update(const uint32&);
	void DelayedUpdate(const uint32 diff);
	//void RelocationNotify();
	void UnloadAll();
	bool CanEnter(Player* player);

	Map* CreateInstance(const uint32 mapId, Player * player);
	Map* FindMap(uint32 InstanceId) const {return _FindMap(InstanceId);}
	bool DestroyInstance(InstancedMaps::iterator &itr);

	void AddGridMapReference(const GridPair &p)
	{
		++GridMapReference[p.x_coord][p.y_coord];
		SetUnloadReferenceLock(GridPair(63-p.x_coord, 63-p.y_coord), true);
	}

	void RemoveGridMapReference(GridPair const& p)
	{
		--GridMapReference[p.x_coord][p.y_coord];
		if (!GridMapReference[p.x_coord][p.y_coord])
		SetUnloadReferenceLock(GridPair(63-p.x_coord, 63-p.y_coord), false);
	}

	InstancedMaps &GetInstancedMaps() {return m_InstancedMaps;}
	virtual void InitVisibilityDistance();

private:

	InstanceMap* CreateInstance(uint32 InstanceId, InstanceSave *save, Difficulty difficulty);
	BattlegroundMap* CreateBattleground(uint32 InstanceId, Battleground* bg);

	InstancedMaps m_InstancedMaps;

	Map* _FindMap(uint32 InstanceId) const
	{
		InstancedMaps::const_iterator i = m_InstancedMaps.find(InstanceId);
		return(i == m_InstancedMaps.end() ? NULL : i->second);
	}

	uint16 GridMapReference[MAX_NUMBER_OF_GRIDS][MAX_NUMBER_OF_GRIDS];
};
#endif
