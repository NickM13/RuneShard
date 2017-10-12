#pragma once
#include "..\VoxelMatrix.h"

class NvmFormat
{
public:
	static void loadModel(std::string p_fileName, std::vector<VoxelMatrix*> &p_matrixList);
};
