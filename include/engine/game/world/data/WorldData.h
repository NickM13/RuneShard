#pragma once

#include "Chunk.h"

#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector2.h"
#include "engine\utils\variable\datatype\Vector3.h"

// Hold the data of the world that is checked for collisions
struct WorldData {
	Vector3<Sint32> m_worldSize;
	std::vector<Chunk*>** m_chunkData;

	void addChunk(Vector2<Sint32> p_chunk);
	void setVoxel(Vector3<Sint32> p_pos, Voxel p_voxel);
	Voxel getVoxel(Vector3<Sint32> p_pos);
	Uint16 getVoxelId(Vector3<Sint32> p_pos);
	bool castRay(Vector3<GLfloat> p_start, Vector3<GLfloat> p_direction, GLdouble &p_near, GLdouble &p_far, Sint8 &p_face); // Make sure p_near = 0 if starting fresh
	bool castBox(Vector3<GLfloat> p_start, Vector3<GLfloat> p_dimension, Vector3<GLfloat> p_direction, GLdouble &p_near, Sint8 &p_face);
};
