#include "engine\gfx\model\VoxelModel.h"

#include "engine\utils\Utilities.h"

#include <fstream>
#include <iostream>

VoxelModel::VoxelModel() {

}
VoxelModel::~VoxelModel() {
	m_matrixList.clear();
}

Vector3<GLfloat> VoxelModel::getModelPos() {
	Vector3<GLfloat> _pos = Vector3<GLfloat>(1000, 1000, 1000);
	for(VoxelMatrix* m : m_matrixList) {
		_pos.x = min(_pos.x, m->getPos().x);
		_pos.x = min(_pos.x, m->getPos().x);
		_pos.x = min(_pos.x, m->getPos().x);
	}
	return _pos;
}
Vector3<Sint32> VoxelModel::getModelSize() {
	Vector3<Sint32> _size = {};
	for(VoxelMatrix* m : m_matrixList) {
		_size.x = max(_size.x, m->getSize().x);
		_size.x = max(_size.x, m->getSize().x);
		_size.x = max(_size.x, m->getSize().x);
	}
	return _size;
}
std::vector<VoxelMatrix*>& VoxelModel::getMatrixList() {
	return m_matrixList;
}
void VoxelModel::createShadow() {

}
void VoxelModel::render() {
	for(Uint16 i = 0; i < m_matrixList.size(); i++)
		m_matrixList[i]->render();
}
