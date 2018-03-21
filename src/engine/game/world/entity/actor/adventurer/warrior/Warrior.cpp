#include "engine\game\world\entity\actor\adventurer\warrior\Warrior.h"
#include "engine\game\world\entity\actor\ability\warrior\AWCharge.h"
#include "engine\game\world\entity\actor\ability\warrior\AWShield.h"
#include "engine\game\world\entity\actor\ability\warrior\AWSwordSwing.h"

Warrior::Warrior(Vector3<GLfloat> p_size)
	: Adventurer(p_size) {
	m_stats.m_health = m_stats.m_maxHealth = 100;
	m_abilityMap.insert({Bind(Bind::MOUSE, GLFW_MOUSE_BUTTON_LEFT), new AWSwordSwing(m_id)});
	m_abilityMap.insert({Bind(Bind::MOUSE, GLFW_MOUSE_BUTTON_RIGHT), new AWShield(m_id)});
	m_abilityMap.insert({Bind(Bind::KEYBOARD, '1'), new AWCharge(m_id)});
}
