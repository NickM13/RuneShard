#pragma once
#include "engine\utils\LOpenGL.h"
#include "engine\utils\variable\manager\TextureManager.h"

class LTexture {
private:
	static bool m_isInit;
public:
	static void init();
	// Use MTexture::getTexture!!!
	static Texture* loadTexture(std::string src);
	static void freeTex(GLuint id = -1);
};
