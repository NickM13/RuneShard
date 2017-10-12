#include "engine\gfx\model\VoxelModel.h"

#include "engine\utils\Utilities.h"

#include <fstream>
#include <iostream>

VoxelModel::VoxelModel(std::string p_fileName)
{
	p_fileName = "res\\model\\" + p_fileName;
	NvmFormat::loadModel(p_fileName, m_matrixList);
}
VoxelModel::~VoxelModel()
{
	m_matrixList.clear();
}

void VoxelModel::render()
{
	for(Uint16 i = 0; i < m_matrixList.size(); i++)
		m_matrixList[i]->render();
}
