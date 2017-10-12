#pragma once

#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector3.h"
#include "engine\utils\variable\manager\VoxelManager.h"

#include "engine\gfx\mesh\VoxelMesh.h"

#include <string>

struct VoxelMatrix
{
public:
	VoxelMatrix(std::string p_name, Vector3<GLfloat> p_pos = {}, Vector3<Sint16> p_size = {});
	VoxelMatrix(VoxelMatrix&);
	~VoxelMatrix();
	void operator=(VoxelMatrix&);

	void setName(std::string p_name) { m_name = p_name; }
	std::string getName() { return m_name; };

	void setPosition(Vector3<GLfloat> p_pos);
	void addPosition(Vector3<GLfloat> p_pos);
	Vector3<GLfloat> getPos() { return m_pos; }
	void setSize(Vector3<Sint32> p_size);
	Vector3<Sint32> getSize() { return m_size; }

	void shiftVoxels(Vector3<Sint32> p_direction);
	bool setVoxel(Vector3<Sint32> p_pos, Voxel p_voxel);
	Voxel getVoxel(Vector3<Sint32> p_pos);
	Uint16 getVoxelId(Vector3<Sint32> p_pos);

	void update();
	void render();
	void rasterize();

private:
	std::string m_name;
	Vector3<GLfloat> m_pos;
	Vector3<Sint16> m_size;

	Uint16*** m_voxelData;
	Sint8*** m_faceData;
	VoxelMesh* m_mesh;

	bool m_needsRasterize;
};
