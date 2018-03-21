#pragma once

#include "engine\utils\Utilities.h"
#include "engine\game\world\entity\actor\Actor.h"

class HUDComponent {
protected:
	std::string m_compName; // Unique component name
	Vector2<Sint32> m_pos, m_size;
	static Actor* m_actor; // Global HUD actor
public:
	HUDComponent(std::string p_compName) : m_compName(p_compName) {}
	static void setActor(Actor* p_actor) { m_actor = p_actor; }

	HUDComponent* setPosition(Vector2<Sint32> p_pos) { m_pos = p_pos; return this; }
	HUDComponent* setSize(Vector2<Sint32> p_size) { m_size = p_size; return this; }

	virtual void inputComponent() = 0;
	void input();
	virtual void updateComponent(GLfloat p_deltaTime) = 0;
	void update(GLfloat p_deltaTime);
	virtual void renderComponent() = 0;
	void render();
};
