#pragma once

#define CHUNK_SIZE 32

#include "engine\utils\variable\manager\VoxelManager.h"
#include "engine\gfx\mesh\VoxelMesh.h"

struct Chunk
{
public:
	Chunk();
	~Chunk();

	void setVoxel(Vector3<Sint32> p_pos, Voxel p_voxel);
	Voxel getVoxel(Vector3<Sint32> p_pos);
	Uint16 getVoxelId(Vector3<Sint32> p_pos);

	void update();
	void render();

	void rasterize();

private:
	Uint16*** m_voxelData;
	Sint8*** m_faceData;
	VoxelMesh* m_mesh;

	bool m_needsRasterize;
};
