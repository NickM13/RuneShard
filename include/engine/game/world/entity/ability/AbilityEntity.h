#pragma once

#include "..\Entity.h"

class AbilityEntity : public Entity {
protected:

public:
	AbilityEntity() {
		m_size = {1, 1, 1};
	}
	virtual void update(WorldData p_world, GLfloat p_deltaTime) {

		m_velocity = m_velocity - Vector3<GLfloat>{0, m_weight, 0} * p_deltaTime;
		Vector3<GLfloat> _velocity = m_velocity * p_deltaTime * 10;
		GLdouble _near = 0, _far = 1;
		Sint8 _face = 0;
		while(_velocity.getLength() > 0) {
			p_world.castRay(m_position, _velocity, _near, _far, _face);

			if(_near < 1 && _face != 0) {
				m_position.x += _velocity.x * _near;
				m_position.y += _velocity.y * _near;
				m_position.z += _velocity.z * _near;
				_velocity = _velocity * (1.f - _near);
				if(_face & (FACE_NORTH | FACE_SOUTH)) {
					m_velocity.x = -m_velocity.x * m_bounciness;
					_velocity.x = -_velocity.x * m_bounciness;
				}
				if(_face & (FACE_TOP | FACE_BOTTOM)) {
					m_velocity.y = -m_velocity.y * m_bounciness;
					_velocity.y = -_velocity.y * m_bounciness;
				}
				if(_face & (FACE_EAST | FACE_WEST)) {
					m_velocity.z = -m_velocity.y * m_bounciness;
					_velocity.z = -_velocity.y * m_bounciness;
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
		m_health -= p_deltaTime;
	}
	virtual void renderModel() {
		MVoxelModel::getVoxelModel("fireball.nvm")->render();
	}
};
