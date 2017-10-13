#include "engine\game\world\entity\character\Character.h"
#include "engine\game\world\World.h"
#include "engine\sfx\Sound.h"
#include <iostream>

Character::Character(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation) {
	m_size = p_size;
	m_position = p_position;
	m_rotation = p_rotation;
	setMoveSpeed(100);
	setJumpHeight(13);
	m_airJumps = 100;
	m_onGround = false;
	m_noClip = false;
}

void Character::move(Vector3<GLfloat> p_direction) {
	m_acceleration = Vector3<GLfloat>(p_direction.x, 0, p_direction.z).getNormal();
}
void Character::turn(Vector3<GLfloat> p_rotation) {
	m_rotation = m_rotation + p_rotation;

	if(m_rotation.x < -90)
		m_rotation.x = -90;
	if(m_rotation.x > 90)
		m_rotation.x = 90;
	if(m_rotation.y < 0)
		m_rotation.y += 360;
	if(m_rotation.y > 360)
		m_rotation.y -= 360;
}

void Character::input() {
	Vector3<GLfloat> dev;
	if(GKey::keyDown(GLFW_KEY_E)) {
		for(Uint16 i = 0; i < 200; i++) {
			dev = Vector3<GLfloat>(rand() % 32 - 16, rand() % 32 - 16, rand() % 32 - 16).getNormal() / 2.f;
			MParticle::getInstance().addUnit(new ParticlePuff(getCenter(), m_velocity + (getLookVector() + dev).getNormal() * 2));
		}
		m_soundJump.play();
	}
}

void Character::render() {
	Entity::render();
	Entity::renderShadow();
}
