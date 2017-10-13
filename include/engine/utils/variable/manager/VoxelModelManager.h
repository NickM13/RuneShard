#pragma once
#include "engine\gfx\model\VoxelModel.h"
#include "Manager.h"

class MVoxelModel {
private:
	static ManagerMap<std::string, VoxelModel*> m_manager;
public:
	static VoxelModel* getVoxelModel(std::string p_filePath);
};
