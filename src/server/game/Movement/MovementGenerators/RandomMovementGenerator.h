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

#ifndef FRENCHCORE_RANDOMMOTIONGENERATOR_H
#define FRENCHCORE_RANDOMMOTIONGENERATOR_H

#include "MovementGenerator.h"
#include "DestinationHolder.h"
#include "Traveller.h"

template<class T>
class RandomMovementGenerator: public MovementGeneratorMedium<T,
		RandomMovementGenerator<T> > {
public:
	// Wander dist is related on db spawn dist. So what if we wanna set eandom movement on summoned creature?!
	RandomMovementGenerator(float spawn_dist = 0.0f) :
			i_nextMoveTime(0), wander_distance(spawn_dist) {
	}

	void _setRandomLocation(T &);
	void Initialize(T &);
	void Finalize(T &);
	void Reset(T &);
	bool Update(T &, const uint32 &);
	bool GetDestination(float &x, float &y, float &z) const;
	void UpdateMapPosition(uint32 mapid, float &x, float &y, float &z) {
		i_destinationHolder.GetLocationNow(mapid, x, y, z);
	}
	MovementGeneratorType GetMovementGeneratorType() {
		return RANDOM_MOTION_TYPE;
	}
private:
	TimeTrackerSmall i_nextMoveTime;

	DestinationHolder<Traveller<T> > i_destinationHolder;
	float wander_distance;
	uint32 i_nextMove;
};
#endif
