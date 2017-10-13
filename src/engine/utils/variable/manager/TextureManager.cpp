#include "engine\utils\variable\manager\TextureManager.h"
#include "engine\gfx\LTexture.h"

ManagerMap<std::string, Texture*> MTexture::m_manager;

Texture* MTexture::getTexture(std::string p_filePath) {
	if(m_manager.contains(p_filePath)) {
		return m_manager.getUnit(p_filePath);
	}
	else {
		Texture* tex = LTexture::loadTexture(p_filePath);
		m_manager.addUnit(p_filePath, tex);
		return tex;
	}
}
