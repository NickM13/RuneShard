#pragma once

#include "Chunk.h"

#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector2.h"
#include "engine\utils\variable\datatype\Vector3.h"

// Hold the data of the world that is checked for collisions
class WorldData
{
public:
	Vector3<Sint32> m_worldSize;
	std::vector<Chunk*>** m_chunkData;

	void addChunk(Vector2<Sint32> p_chunk);

	void setVoxel(Vector3<Sint32> p_pos, Voxel p_voxel);
	Voxel getVoxel(Vector3<Sint32> p_pos);
	Uint16 getVoxelId(Vector3<Sint32> p_pos);

	void castRay(Vector3<GLfloat> p_start, Vector3<GLfloat> p_direction, GLfloat &p_near, Sint8 &p_face); // Make sure p_near = 0 if starting fresh
	void castBox(Vector3<GLfloat> p_start, Vector3<GLfloat> p_dimension, Vector3<GLfloat> p_direction, GLfloat &p_near, Sint8 &p_face);
};
