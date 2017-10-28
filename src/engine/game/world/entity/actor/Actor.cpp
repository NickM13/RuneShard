#include "engine\game\world\entity\actor\Actor.h"
#include "engine\game\world\World.h"
#include "engine\sfx\Sound.h"
#include <iostream>

Actor::Actor(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation) {
	m_size = p_size;
	m_position = p_position;
	m_rotation = p_rotation;
	setMoveSpeed(100);
	setJumpHeight(13);
	m_airJumps = 100;
	m_onGround = false;
	m_noClip = false;
}

Actor* Actor::setModel(VoxelModel* p_voxelModel) {
	m_voxelModel = p_voxelModel;
	return this;
}

Actor* Actor::setName(std::string p_name) {
	m_name = p_name;
	return this;
}
Actor* Actor::setMoveSpeed(GLfloat p_moveSpeed) {
	m_moveSpeed = p_moveSpeed;
	return this;
}
Actor* Actor::setJumpHeight(GLfloat p_jumpHeight) {
	m_jumpHeight = sqrt(p_jumpHeight + 0.025f) / sqrt(5.f / GGameState::m_gravity);
	return this;
}

void Actor::move(Vector3<GLfloat> p_direction) {
	m_acceleration = Vector3<GLfloat>(p_direction.x, 0, p_direction.z).getNormal();
}
void Actor::turn(Vector3<GLfloat> p_rotation) {
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
void Actor::jump() {
	if(m_onGround || m_noClip) {
		m_velocity.y = m_jumpHeight;
	}
	else if(m_airJumps > 0) {
		m_velocity.y = m_jumpHeight;
		m_airJumps--;
	}
}

void Actor::abilityDash() {

}
void Actor::abilityLeft() {

}
void Actor::abilityRight() {

}
void Actor::ability1() {

}
void Actor::ability2() {

}

void Actor::updatePhysics(WorldData p_world, GLfloat p_deltaTime) {
	m_velocity.y -= p_deltaTime * GGameState::m_gravity;
}
void Actor::updateCollision(WorldData p_world, GLfloat p_deltaTime) {
	Vector3<GLfloat> _velocity = m_velocity;
	m_velocity.y = m_velocity.y + m_acceleration.y * (p_deltaTime * m_moveSpeed);
	if(m_onGround) {
		m_velocity.x += m_acceleration.x * (p_deltaTime * m_moveSpeed);
		m_velocity.z += m_acceleration.z * (p_deltaTime * m_moveSpeed);
		m_velocity.x /= 2.f;
		m_velocity.z /= 2.f;
	}
	else {
		m_velocity.x += m_acceleration.x * (p_deltaTime * m_moveSpeed / 5);
		m_velocity.z += m_acceleration.z * (p_deltaTime * m_moveSpeed / 5);
		m_velocity.x /= 1.1f;
		m_velocity.z /= 1.1f;
	}
	if(abs(m_velocity.x) < 0.0001f)
		m_velocity.x = 0;
	if(abs(m_velocity.z) < 0.0001f)
		m_velocity.z = 0;
	_velocity = ((_velocity + m_velocity) / 2) * (p_deltaTime * 10);

	GLdouble _near = 0;
	Sint8 _face = 0;
	if(m_noClip) {
		m_position = m_position + _velocity;
	}
	else {
		m_onGround = false;
		while(_velocity.getLength() > 0) {
			p_world.castBox(m_position - Vector3<GLfloat>(m_size.x / 2, 0, m_size.z / 2), m_size, _velocity, _near, _face);
			if(_near < 1) {
				m_position.x += _velocity.x * _near;
				m_position.y += _velocity.y * _near;
				m_position.z += _velocity.z * _near;
				_velocity = _velocity * (1.f - _near);
				if(_face & (FACE_NORTH | FACE_SOUTH)) {
					if(m_velocity.x < 0)
						m_position.x = roundf(m_position.x - m_size.x / 2) + m_size.x / 2;
					else
						m_position.x = roundf(m_position.x + m_size.x / 2) - m_size.x / 2;
					m_velocity.x = 0;
					_velocity.x = 0;
				}
				if(_face & (FACE_TOP | FACE_BOTTOM)) {
					if(m_velocity.y < 0) {
						m_position.y = roundf(m_position.y);
						m_onGround = true;
					}
					else
						m_position.y = roundf(m_position.y) + (1.f - fmodf(m_size.y, 1));
					m_velocity.y = 0;
					_velocity.y = 0;
				}
				if(_face & (FACE_EAST | FACE_WEST)) {
					if(m_velocity.z < 0)
						m_position.z = roundf(m_position.z - m_size.z / 2) + m_size.z / 2;
					else
						m_position.z = roundf(m_position.z + m_size.z / 2) - m_size.z / 2;
					m_velocity.z = 0;
					_velocity.z = 0;
				}

				_near = 0;
			}
			else {
				m_position.x += _velocity.x;
				m_position.y += _velocity.y;
				m_position.z += _velocity.z;
				_velocity = {};
			}
		}
	}
}
void Actor::renderModel() {
	if(m_voxelModel) {
		glPushMatrix();
		{
			glRotatef(-m_rotation.y + 180, 0, 1, 0);
			glScalef(1.f / 16, 1.f / 16, 1.f / 16);
			m_voxelModel->render();
		}
		glPopMatrix();
	}
}

std::vector<Actor*> MActor::m_actorList;
