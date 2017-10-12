#pragma once

#include "..\World.h"

class WorldIsland : public World
{
private:
	virtual void generate(Vector2<Sint32> p_worldSize);
};
