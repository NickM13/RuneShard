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
	Vector3<GLfloat> m_pos;
	Vector3<GLfloat> m_vel;
	GLfloat m_weight;

	Particle(GLfloat p_life, GLfloat p_size, Color p_color, Vector3<GLfloat> p_pos, Vector3<GLfloat> p_vel, GLfloat p_weight)
	{
		m_maxLife = p_life;
		m_life = p_life;
		m_size = p_size;
		m_color = p_color;
		m_pos = p_pos;
		m_vel = p_vel;
		m_weight = p_weight;
	};

	Particle(Vector3<GLfloat> p_pos = {}, Vector3<GLfloat> p_vel = {})
	{
		m_life = 10.f;
		m_size = 3.f;
		m_color = MColor::getInstance().getUnit(Uint16(rand() % MColor::getInstance().getUnitList().size()));
		m_pos = p_pos;
		m_vel = p_vel;
		m_weight = 0;
	}

	virtual void update(WorldData &p_world, GLfloat p_updateTime);
	virtual void render();
	GLfloat getLife();
};

struct ParticlePuff : public Particle
{
	ParticlePuff(GLfloat p_life, GLfloat p_size, Color p_color, Vector3<GLfloat> p_pos, Vector3<GLfloat> p_vel, GLfloat p_weight)
	{
		m_maxLife = p_life;
		m_life = p_life;
		m_size = p_size;
		m_color = p_color;
		m_pos = p_pos;
		m_vel = p_vel;
		m_weight = p_weight;
	};

	ParticlePuff(Vector3<GLfloat> p_pos = {}, Vector3<GLfloat> p_vel = {})
	{
		m_maxLife = m_life = 2.f;
		m_size = 1.f;
		GLfloat r = (rand() % 4) / 32.f;
		m_color = Color(r + 0.25f, r + 0.25f, r + 0.25f, 1.f);
		m_pos = p_pos;
		m_vel = p_vel;
		m_weight = 0;
	}

	void update(WorldData &p_world, GLfloat p_updateTime);
	void render();
};

class MParticle : public ManagerEntity<Particle*>
{

};
