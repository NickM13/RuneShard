#pragma once

#include "VoxelMatrix.h"
#include "load\NvmFormat.h"
#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector3.h"
#include "engine\utils\variable\manager\VoxelManager.h"

#include "engine\gfx\mesh\VoxelMesh.h"

#include <string>
#include <vector>

class VoxelModel
{
private:
	std::vector<VoxelMatrix*> m_matrixList;

public:
	VoxelModel(std::string p_fileName);
	~VoxelModel();

	void render();
};
