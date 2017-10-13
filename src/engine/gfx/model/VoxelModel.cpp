#include "engine\gfx\model\VoxelModel.h"

#include "engine\utils\Utilities.h"

#include <fstream>
#include <iostream>

VoxelModel::VoxelModel() {

}
VoxelModel::~VoxelModel() {
	m_matrixList.clear();
}

std::vector<VoxelMatrix*>& VoxelModel::getMatrixList() {
	return m_matrixList;
}
void VoxelModel::render() {
	for(Uint16 i = 0; i < m_matrixList.size(); i++)
		m_matrixList[i]->render();
}
