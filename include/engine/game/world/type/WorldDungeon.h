#pragma once

#include "..\World.h"
#include "dungeon\lRoom.h"

class WorldDungeon : public World
{
	virtual void generate(Vector2<Sint32> p_worldSize);

	void addRoom(Room& p_room, Vector3<Sint32> p_pos);
};
