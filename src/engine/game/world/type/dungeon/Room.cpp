#include "engine\game\world\type\dungeon\Room.h"
#include "engine\utils\variable\manager\ColorManager.h"

Room::Room(std::string p_roomName, Vector3<Sint32> p_roomSize)
{
	m_roomName = p_roomName;

	m_roomSize = p_roomSize;

	Uint16 noVoxel = MVoxel::getVoxelId(Voxel(0, MColor::getColorId(Color())));
	m_voxelData = new Uint16**[m_roomSize.x];
	for(Uint16 x = 0; x < m_roomSize.x; x++)
	{
		m_voxelData[x] = new Uint16*[m_roomSize.y];
		for(Uint16 y = 0; y < m_roomSize.y; y++)
		{
			m_voxelData[x][y] = new Uint16[m_roomSize.z];
			for(Uint16 z = 0; z < m_roomSize.z; z++)
			{
				m_voxelData[x][y][z] = noVoxel;
			}
		}
	}
}
Room::~Room()
{
	std::cout << m_roomName << std::endl;
	if(m_roomSize.x < 1) return;
	for(Uint16 x = 0; x < m_roomSize.x; x++)
	{
		for(Uint16 y = 0; y < m_roomSize.y; y++)
		{
			delete[] m_voxelData[x][y];
		}
		delete[] m_voxelData[x];
	}
	delete[] m_voxelData;
	m_roomSize = {};
}

void Room::setVoxel(Vector3<Sint32> p_pos, Voxel p_voxel)
{
	m_voxelData[p_pos.x][p_pos.y][p_pos.z] = MVoxel::getVoxelId(p_voxel);
}
Voxel Room::getVoxel(Vector3<Sint32> p_pos)
{
	return MVoxel::getVoxel(m_voxelData[p_pos.x][p_pos.y][p_pos.z]);
}
Uint16 Room::getVoxelId(Vector3<Sint32> p_pos)
{
	return m_voxelData[p_pos.x][p_pos.y][p_pos.z];
}

void Room::fillArea(Vector3<Sint32> p_pos, Vector3<Sint32> p_size, Voxel p_voxel)
{
	for(Sint32 x = 0; x < p_size.x; x++)
	{
		for(Sint32 y = 0; y < p_size.y; y++)
		{
			for(Sint32 z = 0; z < p_size.z; z++)
			{
				setVoxel(p_pos + Vector3<Sint32>(x, y, z), p_voxel);
			}
		}
	}
}

Vector3<Sint32> Room::getRoomSize()
{
	return m_roomSize;
}
Uint16*** Room::getRoomData()
{
	return m_voxelData;
}
