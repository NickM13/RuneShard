#pragma once
#include "..\datatype\Voxel.h"
#include "Manager.h"

class MVoxel {
private:
	static ManagerSet<Voxel> m_manager;
public:
	static Uint32 getVoxelId(Voxel p_voxel);
	static Voxel getVoxel(Uint32 p_id);
};
