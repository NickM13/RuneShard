#include "engine\game\world\camera\hud\component\HUDComponent.h"

Actor* HUDComponent::m_actor = 0;

void HUDComponent::input() {
	inputComponent();
}
void HUDComponent::update(GLfloat p_deltaTime) {
	updateComponent(p_deltaTime);
}
void HUDComponent::render() {
	glPushMatrix();
	{
		glTranslatef(m_pos.x, m_pos.y, 0);
		renderComponent();
	}
	glPopMatrix();
}
