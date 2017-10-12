#pragma once
#include "engine\utils\OpenGL.h"
#include "engine\utils\Singleton.h"
#include "engine\utils\variable\manager\TextureManager.h"

#include <string>

class LTexture
{
public:
	static void init();
	static GLuint getPrevId();
	static GLuint loadImage(std::string src);
	static Texture getImage(std::string src);
	static void freeTex(GLuint id = -1);
private:
	static bool m_hasInit;
	static GLuint m_imgId;
};
