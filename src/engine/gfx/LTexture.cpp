#include "engine\gfx\LTexture.h"

#include "engine\utils\Utilities.h"

#include <IL\il.h>
#include <IL\ilut.h>

bool LTexture::m_isInit = false;

void LTexture::init() {
	if(!m_isInit) {
		ilInit();
		iluInit();
		ilutInit();
		m_isInit = true;
	}
}

Texture *LTexture::loadTexture(std::string src) {
	if(!m_isInit) return 0;
	GLuint m_imgId;
	std::string _src = "res\\texture\\" + src;
	ilGenImages(1, &m_imgId);
	ilBindImage(m_imgId);
	ilLoadImage(_src.c_str());
	ilutRenderer(ILUT_OPENGL);
	m_imgId = ilutGLBindTexImage();
	return new Texture(src, m_imgId, Vector2<Sint32>(Sint32(ilGetInteger(IL_IMAGE_WIDTH)), Sint32(ilGetInteger(IL_IMAGE_HEIGHT))));
}

void LTexture::freeTex(GLuint id) {
	if(!m_isInit) return;
	ilDeleteImage(id);
}
