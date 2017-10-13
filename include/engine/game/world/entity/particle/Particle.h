#pragma once

#include "..\Entity.h"

#include "engine\utils\variable\datatype\Vector3.h"

#include "engine\utils\variable\manager\Manager.h"
#include "engine\utils\variable\manager\ColorManager.h"

#include "engine\game\world\data\WorldData.h"

struct Particle : public Entity
{
protected:
	GLfloat m_size;
	Color m_color;
	GLfloat m_bounciness;
	GLfloat m_weight;
public:
	Particle();
	Particle(Vector3<GLfloat> p_position, Vector3<GLfloat> p_velocity, GLfloat p_size, GLfloat p_life, Color p_color, GLfloat p_weight);

	virtual void update(WorldData &p_world, GLfloat p_updateTime);
	virtual void render();

	GLfloat getLife() const { return m_health; }
};

struct ParticlePuff : public Particle
{
public:
	ParticlePuff(Vector3<GLfloat> p_position, Vector3<GLfloat> p_velocity, GLfloat p_size, GLfloat p_life, Color p_color, GLfloat p_weight);

	void update(WorldData &p_world, GLfloat p_updateTime);
	void render();
};

class MParticle
{
private:
	static std::vector<Particle*> m_particleList;
public:
	static void addParticle(Particle* p_particle) {
		m_particleList.push_back(p_particle);
	}
	static void input() {
		for(Sint32 i = 0; i < Sint32(m_particleList.size()); i++) {
			m_particleList[i]->input();
		}
	}
	static void update(WorldData &p_world, GLfloat p_updateTime) {
		for(Sint32 i = 0; i < Sint32(m_particleList.size()); i++) {
			m_particleList[i]->update(p_world, p_updateTime);
			if(!m_particleList[i]->exists()) {
				delete m_particleList[i];
				m_particleList.erase(m_particleList.begin() + i);
				i--;
			}
		}
	}
	static void render() {
		for(Sint32 i = 0; i < Sint32(m_particleList.size()); i++) {
			m_particleList[i]->render();
		}
	}
};