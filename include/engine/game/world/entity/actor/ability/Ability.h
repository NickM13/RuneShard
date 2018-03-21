#pragma once
#include "engine\utils\Utilities.h"
#include "engine\utils\variable\manager\VoxelModelManager.h"
#include "engine\game\world\entity\projectile\Projectile.h"

class Ability {
protected:
	Sint32 m_casterId;
	std::string m_abilityName;
	GLfloat m_cooldown, m_lastUse;
	GLfloat m_resourceCost;

	virtual void pressAction();
	virtual void releaseAction();
	virtual void updateAction();
public:
	Ability(Sint32 p_casterId);

	std::string getName() const { return m_abilityName; }
	GLfloat getCooldown() const { return m_cooldown; }
	bool isAvailable() const { return ((glfwGetTime() + m_cooldown) - m_lastUse) > 0; }
	GLfloat getResourceCost() const { return m_resourceCost; }

	virtual void press();
	virtual void release();
	virtual void update();
};

// Typically Left-click attacks
class AbilityBasic : public Ability {
protected:
public:
	AbilityBasic(Sint32 p_casterId);

	virtual void press();
	virtual void release();
};

class AbilityHold : public Ability {
protected:
	bool m_isActive;
public:
	AbilityHold(Sint32 p_casterId);

	virtual void press();
	virtual void release();
	virtual void update();
};

class AbilityCharge : public AbilityHold {
protected:
	bool m_isActive;
public:
	AbilityCharge(Sint32 p_casterId);

	virtual void press();
	virtual void release();
	virtual void update();
};
