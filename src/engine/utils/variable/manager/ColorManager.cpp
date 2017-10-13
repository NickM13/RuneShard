#include "engine\utils\variable\manager\ColorManager.h"

ManagerSet<Color> MColor::m_manager;

Uint32 MColor::getColorId(Color p_voxel) {
	return m_manager.getUnitId(p_voxel);
}
Color MColor::getColor(Uint32 p_id) {
	return m_manager.getUnit(p_id);
}
