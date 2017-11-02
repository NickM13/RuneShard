#include "engine\game\world\entity\actor\Actor.h"
#include "engine\game\world\World.h"
#include "engine\sfx\Sound.h"
#include <iostream>

Actor::Actor(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation) {
	m_size = p_size;
	m_position = p_position;
	m_rotation = p_rotation;
	setMoveSpeed(100);
	setJumpHeight(2.5);
	m_maxAirJumps = 1;
	m_isSprinting = false;
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
	m_stats.m_moveSpeed = p_moveSpeed;
	return this;
}
Actor* Actor::setJumpHeight(GLfloat p_jumpHeight) {
	m_stats.m_jumpHeight = (sqrt(p_jumpHeight + 0.025f) / sqrt(5.f / GGameState::m_gravity)) * sqrt(10);
	return this;
}

void Actor::setMovement(Vector3<GLfloat> p_direction) {
	m_tVelocity = Vector3<GLfloat>(p_direction.x, 0, p_direction.z).getNormal() * m_stats.m_moveSpeed;
	if(m_isSprinting) m_tVelocity = m_tVelocity * 2;
}
void Actor::setMovement(Direction p_direction) {
	switch(p_direction) {
	case FORWARD: setMovement(Math::computeDirection({0, m_rotation.y, 0}));	break;
	case RIGHT: setMovement(Math::computeDirection({0, m_rotation.y + 90, 0})); break;
	case BACK: setMovement(Math::computeDirection({0, m_rotation.y + 180, 0})); break;
	case LEFT: setMovement(Math::computeDirection({0, m_rotation.y + 270, 0})); break;
	}
}
void Actor::addMovement(Vector3<GLfloat> p_direction) {
	setMovement(m_tVelocity + Vector3<GLfloat>(p_direction.x, 0, p_direction.z).getNormal() * m_stats.m_moveSpeed * (m_isSprinting ? 1.5f : 1));
}
void Actor::addMovement(Direction p_direction) {
	switch(p_direction) {
	case FORWARD: addMovement(Math::computeDirection({0, m_rotation.y, 0}));	break;
	case RIGHT: addMovement(Math::computeDirection({0, m_rotation.y + 90, 0})); break;
	case BACK: addMovement(Math::computeDirection({0, m_rotation.y + 180, 0})); break;
	case LEFT: addMovement(Math::computeDirection({0, m_rotation.y + 270, 0})); break;
	}
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
		m_velocity.y = m_stats.m_jumpHeight;
	}
	else if(m_airJumps > 0) {
		m_velocity.y = m_stats.m_jumpHeight;
		m_airJumps--;
		m_airJumpBurst = 0.2f;
	}
}

void Actor::abilityInput() {
	for(std::pair<ControlBind, Ability*> ability : m_abilityMap) {
		switch(ability.first.hardware) {
		case ControlBind::MOUSE:
			if(GKey::keyPressed(ability.first.id)) ability.second->press();
			if(GKey::keyReleased(ability.first.id)) ability.second->release();
			break;
		case ControlBind::KEYBOARD:
			if(GKey::keyPressed(ability.first.id)) ability.second->press();
			if(GKey::keyReleased(ability.first.id)) ability.second->release();
		default: break;
		}
	}
}
void Actor::abilityUpdate() {
	for(std::pair<ControlBind, Ability*> ability : m_abilityMap) {
		ability.second->update();
	}
}
void Actor::abilityRender() {

}

void Actor::updatePhysics(WorldData p_world, GLfloat p_deltaTime) {
	m_velocity.y -= p_deltaTime * GGameState::m_gravity;
}
void Actor::updateCollision(WorldData p_world, GLfloat p_deltaTime) {
	Vector3<GLfloat> _velocity = m_velocity;
	updatePhysics(p_world, p_deltaTime);
	if(m_airJumpBurst > 0) {
		m_velocity.x += Math::smoothChange(m_velocity.x, m_tVelocity.x, 30, p_deltaTime);
		m_velocity.z += Math::smoothChange(m_velocity.z, m_tVelocity.z, 30, p_deltaTime);
		m_airJumpBurst -= glfwGetTime();
	}
	else if(m_onGround) {
		m_velocity.x += Math::smoothChange(m_velocity.x, m_tVelocity.x, 10, p_deltaTime);
		m_velocity.z += Math::smoothChange(m_velocity.z, m_tVelocity.z, 10, p_deltaTime);
	}
	else {
		m_velocity.x += Math::smoothChange(m_velocity.x, m_tVelocity.x, 0.25f, p_deltaTime);
		m_velocity.z += Math::smoothChange(m_velocity.z, m_tVelocity.z, 0.25f, p_deltaTime);
	}
	if(abs(m_velocity.x) < 0.0001f)
		m_velocity.x = 0;
	if(abs(m_velocity.z) < 0.0001f)
		m_velocity.z = 0;
	_velocity = ((_velocity + m_velocity) / 2) * (p_deltaTime);

	GLdouble _near = 0;
	Sint8 _face = 0;
	if(m_noClip) {
		m_position = m_position + _velocity;
	}
	else {
		bool _onGround = false;
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
						_onGround = true;
						m_airJumps = m_maxAirJumps;
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
		m_onGround = _onGround;
	}
	m_tVelocity = {};
}
void Actor::update(WorldData p_world, GLfloat p_deltaTime) {
	abilityUpdate();
	Entity::update(p_world, p_deltaTime);
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
Uint32 MActor::m_actorCount = 0;

void MActor::addActor(Actor* p_actor) {
	p_actor->setId(m_actorCount);
	m_actorList.push_back(p_actor);
	m_actorCount++;
}
void MActor::addActor(std::string p_fileName) {
	m_actorList.push_back(new Actor(p_fileName));
}
std::vector<Actor*> MActor::getActorList() {
	return m_actorList;
}
Actor* MActor::getActor(Uint32 p_id) {
	for(Sint16 i = 0; i < Sint16(m_actorList.size()); i++)
		if(m_actorList[i]->getId() == p_id)
			return m_actorList[i];
	return 0;
}
void MActor::input() {
	for(Sint16 i = 0; i < Sint16(m_actorList.size()); i++)
		m_actorList[i]->input();
}
void MActor::update(WorldData &p_world, GLfloat p_updateTime) {
	for(Sint16 i = 0; i < Sint16(m_actorList.size()); i++) {
		m_actorList[i]->update(p_world, p_updateTime);
		if(!m_actorList[i]->exists()) {
			delete m_actorList[i];
			m_actorList.erase(m_actorList.begin() + i);
			i--;
		}
	}
}
void MActor::render() {
	for(Sint16 i = 0; i < Sint16(m_actorList.size()); i++)
		m_actorList[i]->render();
}
