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

#ifndef __FRENCHCORE_VEHICLE_H
#define __FRENCHCORE_VEHICLE_H

#include "ObjectDefines.h"

struct VehicleEntry;
struct Position;
struct VehicleSeatEntry;
class Unit;

enum PowerType {
	POWER_STEAM = 61,
	POWER_PYRITE = 41,
	POWER_HEAT = 101,
	POWER_OOZE = 121,
	POWER_BLOOD = 141,
	POWER_WRATH = 142
};

enum VehicleFlags {
	VEHICLE_FLAG_NO_STRAFE = 0x00000001, // Sets MOVEFLAG2_NO_STRAFE
	VEHICLE_FLAG_NO_JUMPING = 0x00000002, // Sets MOVEFLAG2_NO_JUMPING
	VEHICLE_FLAG_FULLSPEEDTURNING = 0x00000004, // Sets MOVEFLAG2_FULLSPEEDTURNING
	VEHICLE_FLAG_ALLOW_PITCHING = 0x00000010, // Sets MOVEFLAG2_ALLOW_PITCHING
	VEHICLE_FLAG_FULLSPEEDPITCHING = 0x00000020, // Sets MOVEFLAG2_FULLSPEEDPITCHING
	VEHICLE_FLAG_CUSTOM_PITCH = 0x00000040, // If set use pitchMin and pitchMax from DBC, otherwise pitchMin = -pi/2, pitchMax = pi/2
	VEHICLE_FLAG_ADJUST_AIM_ANGLE = 0x00000400, // Lua_IsVehicleAimAngleAdjustable
	VEHICLE_FLAG_ADJUST_AIM_POWER = 0x00000800,
// Lua_IsVehicleAimPowerAdjustable
};

enum VehicleSeatFlags {
	VEHICLE_SEAT_FLAG_HIDE_PASSENGER = 0x00000200, // Passenger is hidden
	VEHICLE_SEAT_FLAG_UNK11 = 0x00000400, // needed for CGCamera__SyncFreeLookFacing
	VEHICLE_SEAT_FLAG_CAN_CONTROL = 0x00000800, // Lua_UnitInVehicleControlSeat
	VEHICLE_SEAT_FLAG_CAN_ATTACK = 0x00004000, // Can attack, cast spells and use items from vehicle?
	VEHICLE_SEAT_FLAG_CAN_ENTER_OR_EXIT = 0x02000000, // Lua_CanExitVehicle - can enter and exit at free will
	VEHICLE_SEAT_FLAG_CAN_SWITCH = 0x04000000, // Lua_CanSwitchVehicleSeats
	VEHICLE_SEAT_FLAG_CAN_CAST = 0x20000000, // Lua_UnitHasVehicleUI
	VEHICLE_SEAT_FLAG_CAN_CAST_MOUNT_SPELL = 0x00001000, // Can cast spells with SPELL_AURA_MOUNTED from seat (possibly 4.x only, 0 seats on 3.3.5a)
	VEHICLE_SEAT_FLAG_UNCONTROLLED = 0x00002000,
// can override !& VEHICLE_SEAT_FLAG_CAN_ENTER_OR_EXIT
};

enum VehicleSeatFlagsB {
	VEHICLE_SEAT_FLAG_B_NONE = 0x00000000,
	VEHICLE_SEAT_FLAG_B_USABLE_FORCED = 0x00000002,
	VEHICLE_SEAT_FLAG_B_TARGETS_IN_RAIDUI = 0x00000008, // Lua_UnitTargetsVehicleInRaidUI
	VEHICLE_SEAT_FLAG_B_EJECTABLE = 0x00000020, // ejectable
	VEHICLE_SEAT_FLAG_B_USABLE_FORCED_2 = 0x00000040,
	VEHICLE_SEAT_FLAG_B_USABLE_FORCED_3 = 0x00000100,
	VEHICLE_SEAT_FLAG_B_CANSWITCH = 0x04000000, // can switch seats
	VEHICLE_SEAT_FLAG_B_VEHICLE_PLAYERFRAME_UI = 0x80000000,
// Lua_UnitHasVehiclePlayerFrameUI - actually checked for flagsb &~ 0x80000000
};

enum VehicleSpells
{
    VEHICLE_SPELL_RIDE_HARDCODED                 = 46598,
    VEHICLE_SPELL_PARACHUTE                      = 45472
};

struct VehicleSeat {
	explicit VehicleSeat(VehicleSeatEntry const *_seatInfo) :
			seatInfo(_seatInfo), passenger(NULL) {
	}
	VehicleSeatEntry const *seatInfo;
	Unit* passenger;
	uint64 Passenger;
};

struct VehicleAccessory {
	explicit VehicleAccessory(uint32 _uiAccessory, int8 _uiSeat, bool _bMinion) :
			uiAccessory(_uiAccessory), uiSeat(_uiSeat), bMinion(_bMinion) {
	}
	uint32 uiAccessory;
	int8 uiSeat;
	uint32 bMinion;
};

struct VehicleScalingInfo {
	uint32 ID;
	float baseItemLevel;
	float scalingFactor;
};

typedef std::vector<VehicleAccessory> VehicleAccessoryList;
typedef std::map<uint32, VehicleAccessoryList> VehicleAccessoryMap;
typedef std::map<uint32, VehicleScalingInfo> VehicleScalingMap;
typedef std::map<int8, VehicleSeat> SeatMap;

class Vehicle {
	friend class Unit;
	friend class WorldSession;
public:
	explicit Vehicle(Unit *unit, VehicleEntry const *vehInfo);
	virtual ~Vehicle();

	void Install();
	void Uninstall();
	void Reset();
	void Die();
	void InstallAllAccessories(uint32 entry);

	Unit *GetBase() const {
		return me;
	}
	VehicleEntry const *GetVehicleInfo() const {
		return m_vehicleInfo;
	}

	bool HasEmptySeat(int8 seatId) const;
	Unit *GetPassenger(int8 seatId) const;
	int8 GetNextEmptySeat(int8 seatId, bool next, bool byAura = false) const;
	uint8 GetAvailableSeatCount() const;

	bool AddPassenger(Unit *passenger, int8 seatId = -1, bool byAura = false);
	void EjectPassenger(Unit* passenger, Unit* controller);
	void RemovePassenger(Unit *passenger);
	void RelocatePassengers(float x, float y, float z, float ang);
	void RemoveAllPassengers();
	void Dismiss();
	bool IsVehicleInUse() {
		return m_Seats.begin() != m_Seats.end();
	}
	void Relocate(Position pos);

	SeatMap m_Seats;

protected:
	uint16 GetExtraMovementFlagsForBase() const;
	VehicleSeatEntry const* GetSeatForPassenger(Unit* passenger);

protected:
	Unit *me;
	VehicleEntry const *m_vehicleInfo;
	uint32 m_usableSeatNum; // Number of seats that match VehicleSeatEntry::UsableByPlayer, used for proper display flags
	uint32 m_bonusHP;

	SeatMap::iterator GetSeatIteratorForPassenger(Unit* passenger);
	void InitMovementInfoForBase();
	void InstallAccessory(uint32 entry, int8 seatId, bool minion = true);
	
};
#endif
