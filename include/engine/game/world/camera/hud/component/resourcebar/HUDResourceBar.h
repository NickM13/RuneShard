#pragma once

#include "engine\gfx\sprite\SpriteAnimation.h"
#include "..\HUDComponent.h"

// Status bar for ingame HUD
class HUDResourceBar : public HUDComponent {
public:
	enum ResourceType {
		HEALTH,
		RESOURCE,
		STAMINA
	};
protected:
	Texture* m_resourceBarTex;
	ResourceType m_resourceType;
	
	GLfloat m_maxResource;
	GLfloat m_currResource;
public:
	HUDResourceBar(std::string p_compName);

	HUDResourceBar* setStatusType(ResourceType p_resourceType) { m_resourceType = p_resourceType; return this; }

	void inputComponent();
	void updateComponent(GLfloat p_deltaTime);
	void renderComponent();
};
