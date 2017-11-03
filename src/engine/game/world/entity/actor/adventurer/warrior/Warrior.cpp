#include "engine\game\world\entity\actor\adventurer\warrior\Warrior.h"
#include "engine\game\world\entity\actor\ability\warrior\AWCharge.h"
#include "engine\game\world\entity\actor\ability\warrior\AWShield.h"

Warrior::Warrior(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation)
	: Adventurer(p_position, p_size, p_rotation) {
	m_abilityMap.insert({Bind(Bind::MOUSE, GLFW_MOUSE_BUTTON_RIGHT), new AWShield(m_id)});
	m_abilityMap.insert({Bind(Bind::KEYBOARD, '1'), new AWCharge(m_id)});
}
