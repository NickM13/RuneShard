#pragma once

#include "..\Entity.h"
#include "engine\game\world\ability\Ability.h"

class Actor : public Entity {
protected:
	std::string m_name;
	GLfloat m_moveSpeed;
	GLfloat m_jumpHeight; // Exact, in voxels
	Uint8 m_maxAirJumps; // For double jumps
	Uint8 m_airJumps;
	VoxelModel* m_voxelModel = 0;

	void updatePhysics(WorldData p_world, GLfloat p_deltaTime);
	void renderModel();
public:
	Actor(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);
	Actor(std::string p_fileName) {};
	~Actor() {};

	Actor* setModel(VoxelModel* p_voxelModel);

	Actor* setName(std::string p_name);
	Actor* setMoveSpeed(GLfloat p_moveSpeed);
	Actor* setJumpHeight(GLfloat p_jumpHeight);

	void move(Vector3<GLfloat> p_direction);
	void turn(Vector3<GLfloat> p_rotation);
	void jump();

	virtual void abilityDash();
	virtual void abilityLeft();
	virtual void abilityRight();
	virtual void ability1();
	virtual void ability2();

	virtual void updateCollision(WorldData p_world, GLfloat p_deltaTime);

	std::string getName() const { return m_name; }
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
	static void addActor(std::string p_fileName) {
		m_actorList.push_back(new Actor(p_fileName));
	}
	static std::vector<Actor*> getActorList() {
		return m_actorList;
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
