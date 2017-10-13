#include "engine\game\world\entity\particle\Particle.h"

void Particle::update(WorldData &p_world, GLfloat p_updateTime)
{
	m_velocity = m_velocity - Vector3<GLfloat>{0, m_weight, 0} * p_updateTime;
	Vector3<GLfloat> _velocity = m_velocity * p_updateTime * 10;
	GLdouble _near = 0, _far = 1;
	Sint8 _face = 0;

	while(_velocity.getLength() > 0.0001f)
	{
		p_world.castRay(m_position, _velocity, _near, _far, _face);
		if(_near < 1 && _face != 0)
		{
			m_position.x += _velocity.x * _near;
			m_position.y += _velocity.y * _near;
			m_position.z += _velocity.z * _near;
			_velocity = _velocity * (1.f - _near);
			if(_face & (FACE_NORTH | FACE_SOUTH))
			{
				m_velocity.x = -m_velocity.x * m_bounciness;
				_velocity.x = -_velocity.x * m_bounciness;
			}
			if(_face & (FACE_TOP | FACE_BOTTOM))
			{
				m_velocity.y = -m_velocity.y * m_bounciness;
				_velocity.y = -_velocity.y * m_bounciness;
			}
			if(_face & (FACE_EAST | FACE_WEST))
			{
				m_velocity.z = -m_velocity.y * m_bounciness;
				_velocity.z = -_velocity.y * m_bounciness;
			}

			_near = 0;
		}
		else
		{
			m_position.x += _velocity.x;
			m_position.y += _velocity.y;
			m_position.z += _velocity.z;
			_velocity = {};
		}
	}
	/*
	while(_vel.getLength() > 0)
	{
		p_world.castBox(m_pos, {m_size / 16.f, m_size / 16.f, m_size / 16.f}, _vel, _near, _face);
		if(_near != 1)
		{
			m_pos.x += _vel.x * _near;
			m_pos.y += _vel.y * _near;
			m_pos.z += _vel.z * _near;
			_vel = _vel * (1.f - _near);
			if(_face & 1)
			{
				if(fabsf(m_vel.x) < 0.05f)
				{
					m_vel.x = _vel.x = 0;
					m_vel.y = m_vel.y * 0.7f;
					_vel.y = _vel.y * 0.7f;
					m_vel.z = m_vel.z * 0.7f;
					_vel.z = _vel.z * 0.7f;
				}
				else
				{
					m_vel.x = -m_vel.x * 0.7f;
					_vel.x = -_vel.x * 0.7f;
					m_vel.y = m_vel.y * 0.7f;
					_vel.y = _vel.y * 0.7f;
					m_vel.z = m_vel.z * 0.7f;
					_vel.z = _vel.z * 0.7f;
				}
			}
			if(_face & 2)
			{
				if(fabsf(m_vel.y) < 0.05f)
				{
					m_vel.x = m_vel.x * 0.7f;
					_vel.x = _vel.x * 0.7f;
					m_vel.y = _vel.y = 0;
					m_vel.z = m_vel.z * 0.7f;
					_vel.z = _vel.z * 0.7f;
				}
				else
				{
					m_vel.x = m_vel.x * 0.7f;
					_vel.x = _vel.x * 0.7f;
					m_vel.y = -m_vel.y * 0.7f;
					_vel.y = -_vel.y * 0.7f;
					m_vel.z = m_vel.z * 0.7f;
					_vel.z = _vel.z * 0.7f;
				}
			}
			if(_face & 4)
			{
				if(fabsf(m_vel.z) < 0.05f)
				{
					m_vel.x = m_vel.x * 0.7f;
					_vel.x = _vel.x * 0.7f;
					m_vel.y = m_vel.y * 0.7f;
					_vel.y = _vel.y * 0.7f;
					m_vel.z = _vel.z = 0;
				}
				else
				{
					m_vel.x = m_vel.x * 0.7f;
					_vel.x = _vel.x * 0.7f;
					m_vel.y = m_vel.y * 0.7f;
					_vel.y = _vel.y * 0.7f;
					m_vel.z = -m_vel.z * 0.7f;
					_vel.z = -_vel.z * 0.7f;
				}
			}

			_near = 0;
		}
		else
		{
			m_pos.x += _vel.x;
			m_pos.y += _vel.y;
			m_pos.z += _vel.z;
			_vel = {};
		}
	}
	*/
	m_life -= p_updateTime;
}
void Particle::render()
{
	glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glScalef(m_size/16, m_size /16, m_size /16);
		glBegin(GL_QUADS);
		{
			m_color.useColor(0.975f, 0.975f, 0.975f, 1);
			glVertex3f(1, 1, 1);
			glVertex3f(-1, 1, 1);
			glVertex3f(-1, -1, 1);
			glVertex3f(1, -1, 1);

			m_color.useColor(0.9f, 0.9f, 0.9f, 1);
			glVertex3f(1, 1, -1);
			glVertex3f(1, -1, -1);
			glVertex3f(-1, -1, -1);
			glVertex3f(-1, 1, -1);

			m_color.useColor(1, 1, 1, 1);
			glVertex3f(1, 1, 1);
			glVertex3f(1, 1, -1);
			glVertex3f(-1, 1, -1);
			glVertex3f(-1, 1, 1);

			m_color.useColor(0.85f, 0.85f, 0.85f, 1);
			glVertex3f(1, -1, 1);
			glVertex3f(-1, -1, 1);
			glVertex3f(-1, -1, -1);
			glVertex3f(1, -1, -1);

			m_color.useColor(0.95f, 0.95f, 0.95f, 1);
			glVertex3f(1, 1, 1);
			glVertex3f(1, -1, 1);
			glVertex3f(1, -1, -1);
			glVertex3f(1, 1, -1);

			m_color.useColor(0.95f, 0.95f, 0.95f, 1);
			glVertex3f(-1, 1, 1);
			glVertex3f(-1, 1, -1);
			glVertex3f(-1, -1, -1);
			glVertex3f(-1, -1, 1);
		}
		glEnd();
	}
	glPopMatrix();
}
GLfloat Particle::getLife()
{
	return m_life;
}



void ParticlePuff::update(WorldData &p_world, GLfloat p_updateTime)
{
	Particle::update(p_world, p_updateTime);
}

void ParticlePuff::render()
{
	GLfloat percent = m_life / m_maxLife;
	GLfloat scale = (1.f - percent) * 2.5f;
	glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glScalef((m_size / 16) * scale, (m_size / 16) * scale, (m_size / 16) * scale);
		glBegin(GL_QUADS);
		{
			m_color.useColor(0.975f, 0.975f, 0.975f, percent);
			glVertex3f(1, 1, 1);
			glVertex3f(-1, 1, 1);
			glVertex3f(-1, -1, 1);
			glVertex3f(1, -1, 1);

			m_color.useColor(0.9f, 0.9f, 0.9f, percent);
			glVertex3f(1, 1, -1);
			glVertex3f(1, -1, -1);
			glVertex3f(-1, -1, -1);
			glVertex3f(-1, 1, -1);

			m_color.useColor(1, 1, 1, percent);
			glVertex3f(1, 1, 1);
			glVertex3f(1, 1, -1);
			glVertex3f(-1, 1, -1);
			glVertex3f(-1, 1, 1);

			m_color.useColor(0.85f, 0.85f, 0.85f, percent);
			glVertex3f(1, -1, 1);
			glVertex3f(-1, -1, 1);
			glVertex3f(-1, -1, -1);
			glVertex3f(1, -1, -1);

			m_color.useColor(0.95f, 0.95f, 0.95f, percent);
			glVertex3f(1, 1, 1);
			glVertex3f(1, -1, 1);
			glVertex3f(1, -1, -1);
			glVertex3f(1, 1, -1);

			m_color.useColor(0.95f, 0.95f, 0.95f, percent);
			glVertex3f(-1, 1, 1);
			glVertex3f(-1, 1, -1);
			glVertex3f(-1, -1, -1);
			glVertex3f(-1, -1, 1);
		}
		glEnd();
	}
	glPopMatrix();
}
