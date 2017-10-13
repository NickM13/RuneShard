#pragma once
#include "Manager.h"
#include "engine\utils\variable\datatype\Texture.h"

class MTexture {
private:
	static ManagerMap<std::string, Texture*> m_manager;
public:
	static Texture* getTexture(std::string p_filePath);
};
