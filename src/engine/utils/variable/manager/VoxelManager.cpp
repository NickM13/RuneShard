#include "engine\utils\variable\manager\VoxelManager.h"

ManagerSet<Voxel> MVoxel::m_manager;

Uint32 MVoxel::getVoxelId(Voxel p_voxel) {
	return m_manager.getUnitId(p_voxel);
}
Voxel MVoxel::getVoxel(Uint32 p_id) {
	return m_manager.getUnit(p_id);
}
