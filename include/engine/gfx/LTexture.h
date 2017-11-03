#pragma once
#include "engine\utils\OpenGL.h"
#include "engine\utils\variable\manager\TextureManager.h"

class LTexture {
private:
	static bool m_isInit;
public:
	static void init();
	static Texture* loadTexture(std::string src);
	static void freeTex(GLuint id = -1);
};
