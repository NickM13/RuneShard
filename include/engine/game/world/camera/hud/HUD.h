#pragma once
#include "engine\utils\Utilities.h"
#include "engine\gfx\LTexture.h"
#include "engine\gfx\sprite\SpriteAnimation.h"
#include "component\LHUDComponent.h"

// Ingame Heads-Up-Display
// A container for HUD Components
class HUD {
private:
	std::vector<HUDComponent*> m_componentList;
public:
	void init(Actor* p_hudActor);

	HUDComponent* addComponent(HUDComponent *p_hudComponent);

	void input();
	void update(GLfloat p_deltaTime);
	void render();
};
