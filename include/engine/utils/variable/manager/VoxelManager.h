#pragma once
#include "..\datatype\Voxel.h"
#include "Manager.h"

class MVoxel : public Manager<Voxel>
{
	MVoxel() { m_unitList.push_back(Voxel(0, 0)); };
};
