#include "engine\game\world\camera\hud\HUD.h"

void HUD::init(Actor* p_hudActor) {
	HUDComponent::setActor(p_hudActor);
}

HUDComponent* HUD::addComponent(HUDComponent *p_hudComponent) {
	m_componentList.push_back(p_hudComponent);
	return p_hudComponent;
}

void HUD::input() {
	for(HUDComponent *comp : m_componentList) {
		comp->input();
	}
}
void HUD::update(GLfloat p_deltaTime) {
	for(HUDComponent *comp : m_componentList) {
		comp->update(p_deltaTime);
	}
}
void HUD::render() {
	for(HUDComponent *comp : m_componentList) {
		comp->render();
	}
}
