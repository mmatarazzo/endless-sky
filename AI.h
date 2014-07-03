/* AI.h
Copyright (c) 2014 by Michael Zahniser

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/

#ifndef AI_H_
#define AI_H_

#include <list>
#include <memory>
#include <string>

class Controllable;
class Point;
class Ship;
class PlayerInfo;



// Interface for ship AIs.
class AI {
public:
	AI();
	
	void UpdateKeys(int keys, PlayerInfo *info);
	void Step(const std::list<std::shared_ptr<Ship>> &ships, const PlayerInfo &info);
	
	
private:
	// Pick a new target for the given ship.
	std::weak_ptr<const Ship> FindTarget(const Ship &ship, const std::list<std::shared_ptr<Ship>> &ships);
	
	void MoveIndependent(Controllable &control, const Ship &ship);
	void MoveEscort(Controllable &control, const Ship &ship);
	
	double TurnBackward(const Ship &ship);
	double TurnToward(const Ship &ship, const Point &vector);
	bool MoveToPlanet(Controllable &control, const Ship &ship);
	bool MoveTo(Controllable &control, const Ship &ship, const Point &target, double radius, double slow);
	void PrepareForHyperspace(Controllable &control, const Ship &ship);
	void CircleAround(Controllable &control, const Ship &ship, const Ship &target);
	void Attack(Controllable &control, const Ship &ship, const Ship &target);
	
	Point StoppingPoint(const Ship &ship);
	// Get a vector giving the direction this ship should aim in in order to do
	// maximum damaged to a target at the given position with its non-turret,
	// non-homing weapons. If the ship has no non-homing weapons, this just
	// returns the direction to the target.
	Point TargetAim(const Ship &ship) const;
	// Fire whichever of the given ship's weapons can hit a hostile target.
	// Return a bitmask giving the weapons to fire.
	int AutoFire(const Ship &ship, const std::list<std::shared_ptr<Ship>> &ships);
	
	void MovePlayer(Controllable &control, const PlayerInfo &info, const std::list<std::shared_ptr<Ship>> &ships);
	
	
private:
	int step;
	
	int keyDown;
	int keyHeld;
	int keyStuck;
};



#endif
