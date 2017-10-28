#pragma once
#include "..\Actor.h"

class Roger : public Actor {
public:
	Roger(Vector3<GLfloat> p_position) 
		: Actor(p_position, {0.9f, 1.8f, 0.9f}, {}) {
		setMoveSpeed(100);
		setJumpHeight(13);
		m_airJumps = 0;
		m_maxHealth = 100;
		setModel(MVoxelModel::getVoxelModel("Roger.nvm"));
		m_name = "Roger";
	}
};
