#pragma once
#include "Vector2.h"
#include "Macros.h"

#include <string>

struct Texture {
private:
	Sint32 m_texId;
	std::string m_name;
	Vector2<Sint32> m_size;

public:
	Texture(std::string p_name = "", Sint32 p_texId = -1, Vector2<Sint32> p_size = {}) {
		m_texId = p_texId;
		m_name = p_name;
		m_size = p_size;
	}
	bool operator==(Texture p_tex) {
		return (m_name == p_tex.m_name && m_size.x == p_tex.m_size.x && m_size.y == p_tex.m_size.y);
	}
	void setName(std::string p_name)
	{ m_name = p_name; }
	Sint32 getId()
	{ return m_texId; }
	std::string getName()
	{ return m_name; }
	Vector2<Sint32> getSize()
	{ return m_size; }
	void render(Vector2<Sint32> p_start = {0, 0}, Vector2<Sint32> p_size = {-1, -1}) {
		p_start.y = m_size.y - p_start.y;
		Vector2<GLfloat> tPos, tSize;
		if(p_size.x < 0) p_size.x = m_size.x - p_start.x;
		if(p_size.y < 0) p_size.y = m_size.y - p_start.y;
		tPos = Vector2<GLfloat>(p_start) / m_size;
		tSize = Vector2<GLfloat>(p_size) / m_size;
		glBindTexture(GL_TEXTURE_2D, m_texId);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(tPos.x, tPos.y);						glVertex2f(0, 0);
			glTexCoord2f(tPos.x + tSize.x, tPos.y);				glVertex2f(p_size.x, 0);
			glTexCoord2f(tPos.x + tSize.x, tPos.y - tSize.y);	glVertex2f(p_size.x, p_size.y);
			glTexCoord2f(tPos.x, tPos.y - tSize.y);				glVertex2f(0, p_size.y);
		}
		glEnd();
	}
};
