#pragma once

#include "Manager.h"
#include "..\datatype\Color.h"

class MColor {
private:
	static ManagerSet<Color> m_manager;
public:
	static Uint32 getColorId(Color p_voxel);
	static Color getColor(Uint32 p_id);
};
