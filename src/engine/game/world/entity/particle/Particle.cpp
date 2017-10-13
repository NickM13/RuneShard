#include "engine\game\world\entity\particle\Particle.h"

Particle::Particle() {
	/*
		   /\       
		  /  \      
		 /,--.\     
		/< () >\    
	   /  `--'  \   
	  /          \  
	 /   fnord?   \ 
	/______________\
	hjm
	*/
}
Particle::Particle(Vector3<GLfloat> p_position, Vector3<GLfloat> p_velocity, GLfloat p_size, GLfloat p_life, Color p_color, GLfloat p_weight) {
	m_maxHealth = p_life;
	m_health = p_life;
	m_size = p_size;
	m_color = p_color;
	m_position = p_position;
	m_velocity = p_velocity;
	m_weight = p_weight;
	m_bounciness = 0.7f;
};

void Particle::update(WorldData &p_world, GLfloat p_updateTime) {
	m_velocity = m_velocity - Vector3<GLfloat>{0, m_weight, 0} * p_updateTime;
	Vector3<GLfloat> _velocity = m_velocity * p_updateTime * 10;
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
	m_health -= p_updateTime;
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

ParticlePuff::ParticlePuff(Vector3<GLfloat> p_position, Vector3<GLfloat> p_velocity, GLfloat p_size, GLfloat p_life, Color p_color, GLfloat p_weight) {
	m_position = p_position;
	m_velocity = p_velocity;
	m_size = p_size;
	m_maxHealth = m_health = p_life;
	m_color = p_color;
	m_weight = p_weight;
	m_bounciness = 0.7f;
}

void ParticlePuff::update(WorldData &p_world, GLfloat p_updateTime) {
	Particle::update(p_world, p_updateTime);
}
void ParticlePuff::render() {
	GLfloat percent = m_health / m_maxHealth;
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

std::vector<Particle*> MParticle::m_particleList;
