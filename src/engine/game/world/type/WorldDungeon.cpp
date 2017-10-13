#include "engine\game\world\type\WorldDungeon.h"

void WorldDungeon::generate(Vector2<Sint32> p_worldSize)
{
	lRoom::init();

	init(p_worldSize);

	addRoom(lRoom::getRoom("Entrance"), {0, 0, 0});

	addActor(m_player);
}

void WorldDungeon::addRoom(Room& p_room, Vector3<Sint32> p_pos)
{
	/*
	Vector3<Sint32> _size = p_room.getRoomSize();
	Uint16*** _data = p_room.getRoomData();
	for(Uint16 x = 0; x < _size.x; x++)
		for(Uint16 y = 0; y < _size.y; y++)
			for(Uint16 z = 0; z < _size.z; z++)
				if(_data[x][y][z])
					setVoxel(p_pos + Vector3<Sint32>(x, y, z), p_room.getVoxel(Vector3<Sint32>(x, y, z)));
	*/
}
