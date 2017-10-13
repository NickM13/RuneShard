#include "engine\game\world\type\dungeon\lRoom.h"

std::vector<Room> lRoom::m_rooms;

void lRoom::init()
{
	Room* room = new Room("Entrance", {32, 32, 32});
	room->fillArea({0, 0, 0}, {32, 1, 32}, Voxel(1, MColor::getColorId(Color(0.6f, 0.6f, 0.6f))));
	addRoom(*room);
}

void lRoom::addRoom(Room& p_room)
{
	m_rooms.push_back(p_room);
}

Room& lRoom::getRoom(std::string p_roomName)
{
	for(Uint16 i = 0; i < Uint16(m_rooms.size()); i++)
	{
		if(p_roomName == m_rooms[i].getName())
		{
			return m_rooms[i];
		}
	}
	return Room("404", {});
}
