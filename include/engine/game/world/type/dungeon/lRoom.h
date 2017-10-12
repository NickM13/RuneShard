#pragma once

#include "Room.h"

class lRoom
{
public:
	static void init();
	static void addRoom(Room& p_room);
	static Room& getRoom(std::string p_roomName);
private:
	static std::vector<Room> m_rooms;
};
