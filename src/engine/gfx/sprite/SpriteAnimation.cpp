#include "engine\gfx\sprite\SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(Texture* p_spriteSheet, GLfloat p_animationTime, bool p_synced) {
	m_spriteSheet = p_spriteSheet;
	m_animationTime = p_animationTime;
	m_synced = p_synced;
}

void SpriteAnimation::pushSprite(Vector2<Sint32> p_pos, Vector2<Sint32> p_size) {
	m_spriteList.push_back(Sprite(p_pos, p_size));
}
void SpriteAnimation::pushSpriteRepeated(Vector2<Sint32> p_start, Vector2<Sint32> p_step, Vector2<Sint32> p_size, Sint32 p_count) {
	for(Sint32 i = 0; i < p_count; i++) {
		m_spriteList.push_back(Sprite(p_start + p_step * i, p_size));
	}
}

void SpriteAnimation::render() {
	Sint16 i;
	Vector2<GLfloat> tPos, tSize;
	if(m_synced) {
		i = fmod(glfwGetTime(), (m_animationTime * m_spriteList.size())) / (m_animationTime * m_spriteList.size()) * m_spriteList.size();
	}
	else {
		m_unsyncedTimer += GScreen::m_deltaTime;
		i = fmod(m_unsyncedTimer, m_animationTime) / m_animationTime * m_spriteList.size();
	}
	glBindTexture(GL_TEXTURE_2D, m_spriteSheet->getId());
	glColor3f(1, 1, 1);
	tPos = Vector2<GLfloat>(m_spriteList[i].pos) / m_spriteSheet->getSize();
	tSize = Vector2<GLfloat>(m_spriteList[i].size) / m_spriteSheet->getSize();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(tPos.x, 1.f - (tPos.y));							glVertex2f(0, 0);
		glTexCoord2f(tPos.x + tSize.x, 1.f - (tPos.y));					glVertex2f(m_spriteList[i].size.x, 0);
		glTexCoord2f(tPos.x + tSize.x, 1.f - (tPos.y + tSize.y));		glVertex2f(m_spriteList[i].size.x, m_spriteList[i].size.y);
		glTexCoord2f(tPos.x, 1.f - (tPos.y + tSize.y));					glVertex2f(0, m_spriteList[i].size.y);
	}
	glEnd();
}

void SpriteAnimation::resetTimer() {
	m_unsyncedTimer = 0;
	m_unsyncedTimerLast = glfwGetTime();
}
