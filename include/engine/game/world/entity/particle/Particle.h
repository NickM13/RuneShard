#pragma once

#include "engine\utils\variable\datatype\Vector3.h"

#include "engine\utils\variable\manager\Manager.h"
#include "engine\utils\variable\manager\ColorManager.h"

#include "engine\game\world\data\WorldData.h"

struct Particle
{
	GLfloat m_maxLife;
	GLfloat m_life;
	GLfloat m_size;
	Color m_color;
	Vector3<GLfloat> m_position;
	Vector3<GLfloat> m_velocity;
	GLfloat m_weight;
	GLfloat m_bounciness;

	Particle(GLfloat p_life, GLfloat p_size, Color p_color, Vector3<GLfloat> p_position, Vector3<GLfloat> p_velocity, GLfloat p_weight)
	{
		m_maxLife = p_life;
		m_life = p_life;
		m_size = p_size;
		m_color = p_color;
		m_position = p_position;
		m_velocity = p_velocity;
		m_weight = p_weight;
		m_bounciness = 0.7f;
	};

	Particle(Vector3<GLfloat> p_pos = {}, Vector3<GLfloat> p_vel = {})
	{
		m_life = 10.f;
		m_size = 3.f;
		m_color = MColor::getInstance().getUnit(Uint16(rand() % MColor::getInstance().getUnitList().size()));
		m_position = p_pos;
		m_velocity = p_vel;
		m_weight = 0;
		m_bounciness = 0.7f;
	}

	virtual void update(WorldData &p_world, GLfloat p_updateTime);
	virtual void render();
	GLfloat getLife();
};

struct ParticlePuff : public Particle
{
	ParticlePuff(GLfloat p_life, GLfloat p_size, Color p_color, Vector3<GLfloat> p_position, Vector3<GLfloat> p_velocity, GLfloat p_weight)
	{
		m_maxLife = p_life;
		m_life = p_life;
		m_size = p_size;
		m_color = p_color;
		m_position = p_position;
		m_velocity = p_velocity;
		m_weight = p_weight;
		m_bounciness = 0.7f;
	};

	ParticlePuff(Vector3<GLfloat> p_pos = {}, Vector3<GLfloat> p_vel = {})
	{
		m_maxLife = m_life = 2.f;
		m_size = 1.f;
		GLfloat r = (rand() % 4) / 32.f;
		m_color = Color(r + 0.25f, r + 0.25f, r + 0.25f, 1.f);
		m_position = p_pos;
		m_velocity = p_vel;
		m_weight = 0;
		m_bounciness = 0.7f;
	}

	void update(WorldData &p_world, GLfloat p_updateTime);
	void render();
};

class MParticle : public ManagerEntity<Particle*>
{

};
