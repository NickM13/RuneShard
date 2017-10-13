#include "engine\utils\variable\manager\VoxelModelManager.h"

ManagerMap<std::string, VoxelModel*> MVoxelModel::m_manager;

VoxelModel* MVoxelModel::getVoxelModel(std::string p_filePath) {
	if(m_manager.contains(p_filePath)) {
		return m_manager.getUnit(p_filePath);
	}
	else {
		VoxelModel* model = new VoxelModel();
		NvmFormat::loadModel("res\\model\\" + p_filePath, model->getMatrixList());
		m_manager.addUnit(p_filePath, model);
		return model;
	}
}
