#pragma once

#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector3.h"

#include "engine\utils\variable\manager\VoxelManager.h"
#include "engine\gfx\mesh\VoxelMesh.h"

struct Room
{
public:
	Room(std::string p_roomName, Vector3<Sint32> p_roomSize);
	~Room();

	void setVoxel(Vector3<Sint32> p_pos, Voxel p_voxel);
	Voxel getVoxel(Vector3<Sint32> p_pos);
	Uint16 getVoxelId(Vector3<Sint32> p_pos);
	std::string getName() { return m_roomName; }

	void fillArea(Vector3<Sint32> p_pos, Vector3<Sint32> p_size, Voxel p_voxel);

	Vector3<Sint32> getRoomSize();
	Uint16*** getRoomData();

protected:
	std::string m_roomName;
	Vector3<Sint32> m_roomSize;
	Uint16*** m_voxelData;
};
