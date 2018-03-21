#pragma once
#include "engine\utils\Utilities.h"
#include "engine\utils\variable\manager\VoxelModelManager.h"
#include "..\Entity.h"

class Projectile : public Entity {
protected:
	std::string m_abilityName;
	GLfloat m_cooldown, m_lastUse;
	GLfloat m_resourceCost;
public:
	Projectile();

	std::string getName() const { return m_abilityName; }

	// Return time between ability uses
	GLfloat getCooldown() const { return m_cooldown; }

	// Return how long until next use
	GLfloat getAvailabilityTime() const { return (glfwGetTime() + m_cooldown) - m_lastUse; }

	virtual void inputProjectile();
	void input();
	virtual void updatePhysics(GLfloat p_updateTime);
	virtual void updateActorCollision();
	virtual void updateWorldCollision(WorldData &p_world);
	virtual void updateProjectile();
	virtual void updateMovement();
	void update(WorldData &p_world, GLfloat p_updateTime);
	virtual void renderProjectile();
	void render();
};

class MProjectile {
private:
	static std::vector<Projectile*> m_projectileList;
	static Uint32 m_actorCount;
public:
	static void create(Projectile* p_ability) {
		m_projectileList.push_back(p_ability);
	}
	static std::vector<Projectile*> getProjectileList() {
		return m_projectileList;
	}
	static void input() {
		for(Sint16 i = 0; i < Sint16(m_projectileList.size()); i++) {
			m_projectileList[i]->input();
		}
	}
	static void update(WorldData &p_world, GLfloat p_updateTime) {
		for(Sint16 i = 0; i < Sint16(m_projectileList.size()); i++) {
			m_projectileList[i]->update(p_world, p_updateTime);
			if(!m_projectileList[i]->exists()) {
				delete m_projectileList[i];
				m_projectileList.erase(m_projectileList.begin() + i);
				i--;
			}
		}
	}
	static void render() {
		for(Sint16 i = 0; i < Sint16(m_projectileList.size()); i++) {
			m_projectileList[i]->render();
		}
	}
};
