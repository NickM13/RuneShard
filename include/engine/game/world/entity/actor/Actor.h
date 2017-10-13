#pragma once

#include "..\Entity.h"

class Actor : public Entity {
protected:
	GLfloat m_moveSpeed;
	GLfloat m_jumpHeight; // Exact, in voxels
	Uint8 m_maxAirJumps; // For double jumps
	Uint8 m_airJumps;
public:
	Actor() {};
	Actor(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);
	Actor(std::string p_fileName) {};
	~Actor() {};

	void setMoveSpeed(GLfloat p_moveSpeed);
	void setJumpHeight(GLfloat p_jumpHeight);
	void jump();

	virtual void move(Vector3<GLfloat> p_direction);
	virtual void turn(Vector3<GLfloat> p_rotation);

	virtual void input();
	virtual void update(WorldData p_world, GLfloat p_deltaTime);
	virtual void render();

	GLfloat getHealth() const { return m_health; };
	GLfloat getMaxHealth() const { return m_maxHealth; };
	void damage(GLfloat amt) { m_health -= amt; };
};

class MActor
{
private:
	static std::vector<Actor*> m_actorList;
public:
	static void addActor(Actor* p_actor) {
		m_actorList.push_back(p_actor);
	}
	static void addActor(std::string p_scriptName) {
		m_actorList.push_back(p_scriptName);
	}
	static void input() {
		for(Sint16 i = 0; i < Sint16(m_actorList.size()); i++) {
			m_actorList[i]->input();
		}
	}
	static void update(WorldData &p_world, GLfloat p_updateTime) {
		for(Sint16 i = 0; i < Sint16(m_actorList.size()); i++) {
			m_actorList[i]->update(p_world, p_updateTime);
			if(!m_actorList[i]->exists()) {
				delete m_actorList[i];
				m_actorList.erase(m_actorList.begin() + i);
				i--;
			}
		}
	}
	static void render() {
		for(Sint16 i = 0; i < Sint16(m_actorList.size()); i++) {
			m_actorList[i]->render();
		}
	}
};
