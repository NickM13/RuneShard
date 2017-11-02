#include "engine\game\world\entity\actor\actors\Roger.h"

Roger::Roger(Vector3<GLfloat> p_position)
	: Warrior(p_position, {0.9f, 1.8f, 0.9f}, {}) {
	setMoveSpeed(15);
	setJumpHeight(4);
	m_airJumps = 1;
	m_stats.m_health = m_stats.m_maxHealth = 100;
	setModel(MVoxelModel::getVoxelModel("Roger.nvm"));
	m_name = "Roger";
}
