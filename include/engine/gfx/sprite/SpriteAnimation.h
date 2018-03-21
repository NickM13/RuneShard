#pragma once
#include "engine\utils\Utilities.h"
#include "engine\gfx\LTexture.h"

class SpriteAnimation {
private:
	struct Sprite {
		Vector2<Sint32> pos, size;
		Sprite(Vector2<Sint32> p_pos, Vector2<Sint32> p_size) 
			: pos(p_pos), size(p_size) {}
	};
	std::vector<Sprite> m_spriteList;

	GLfloat m_animationTime; // Time between sprites
	Texture* m_spriteSheet;

	bool m_synced; // Use glfwGetTime() or unsyncedTimer
	GLfloat m_unsyncedTimer, m_unsyncedTimerLast; // Resets with resetTimer, still runs off of glfwGetTime
public:
	// Synced with glfw time or on own timer
	SpriteAnimation(Texture* p_spriteSheet, GLfloat p_animationTime, bool p_synced = true);

	void pushSprite(Vector2<Sint32> p_pos, Vector2<Sint32> p_size);
	void pushSpriteRepeated(Vector2<Sint32> p_start, Vector2<Sint32> p_step, Vector2<Sint32> p_size, Sint32 p_count);

	void render();

	// For unsynced animation
	void resetTimer();
};
