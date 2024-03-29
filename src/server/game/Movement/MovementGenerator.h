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

#ifndef FRENCHCORE_MOVEMENTGENERATOR_H
#define FRENCHCORE_MOVEMENTGENERATOR_H

#include "Define.h"
#include <ace/Singleton.h>
#include "ObjectRegistry.h"
#include "FactoryHolder.h"
#include "Common.h"
#include "MotionMaster.h"

class Unit;

class MovementGenerator {
public:
	virtual ~MovementGenerator();

	virtual void Initialize(Unit &) = 0;
	virtual void Finalize(Unit &) = 0;

	virtual void Reset(Unit &) = 0;

	virtual bool Update(Unit &, const uint32 &time_diff) = 0;

	virtual MovementGeneratorType GetMovementGeneratorType() = 0;

	virtual void unitSpeedChanged() {
	}

	virtual bool GetDestination(float& /*x*/, float& /*y*/,
			float& /*z*/) const {
		return false;
	}
};

template<class T, class D>
class MovementGeneratorMedium: public MovementGenerator {
public:
	void Initialize(Unit &u) {
		//u->AssertIsType<T>();
		(static_cast<D*>(this))->Initialize(*((T*) &u));
	}
	void Finalize(Unit &u) {
		//u->AssertIsType<T>();
		(static_cast<D*>(this))->Finalize(*((T*) &u));
	}
	void Reset(Unit &u) {
		//u->AssertIsType<T>();
		(static_cast<D*>(this))->Reset(*((T*) &u));
	}
	bool Update(Unit &u, const uint32 &time_diff) {
		//u->AssertIsType<T>();
		return (static_cast<D*>(this))->Update(*((T*) &u), time_diff);
	}
public:
	// will not link if not overridden in the generators
	void Initialize(T &u);
	void Finalize(T &u);
	void Reset(T &u);
	bool Update(T &u, const uint32 &time_diff);
};

struct SelectableMovement: public FactoryHolder<MovementGenerator,
		MovementGeneratorType> {
	SelectableMovement(MovementGeneratorType mgt) :
			FactoryHolder<MovementGenerator, MovementGeneratorType>(mgt) {
	}
};

template<class REAL_MOVEMENT>
struct MovementGeneratorFactory: public SelectableMovement {
	MovementGeneratorFactory(MovementGeneratorType mgt) :
			SelectableMovement(mgt) {
	}

	MovementGenerator* Create(void *) const;
};

typedef FactoryHolder<MovementGenerator, MovementGeneratorType> MovementGeneratorCreator;
typedef FactoryHolder<MovementGenerator, MovementGeneratorType>::FactoryHolderRegistry MovementGeneratorRegistry;
typedef FactoryHolder<MovementGenerator, MovementGeneratorType>::FactoryHolderRepository MovementGeneratorRepository;
#endif
