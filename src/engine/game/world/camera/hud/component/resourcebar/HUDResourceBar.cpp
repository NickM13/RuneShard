#include "engine\game\world\camera\hud\component\resourcebar\HUDResourceBar.h"

HUDResourceBar::HUDResourceBar(std::string p_compName)
	: HUDComponent(p_compName) {
	m_resourceBarTex = MTexture::getTexture("gui\\player\\ResourceBar.png");

	m_size = m_resourceBarTex->getSize();
	m_size.y /= 2;
}

void HUDResourceBar::inputComponent() {

}
void HUDResourceBar::updateComponent(GLfloat p_deltaTime) {
	switch(m_resourceType) {
	case HEALTH:
		m_maxResource = m_actor->getMaxHealth();
		m_currResource = m_actor->getHealth();
		break;
	case STAMINA:

		break;
	case RESOURCE:

		break;
	default:

		break;
	}
}
void HUDResourceBar::renderComponent() {
	GLfloat curr = m_resourceBarTex->getSize().x * (m_currResource / m_maxResource);
	switch(m_resourceType) {
	case HEALTH:
		glColor3f(1, 0, 0);
		break;
	case STAMINA:
		glColor3f(0, 1, 0);
		break;
	case RESOURCE:
		glColor3f(0, 0, 1);
		break;
	default:
		glColor3f(1, 1, 1);
		break;
	}
	m_resourceBarTex->render({0, 0}, Vector2<Sint32>(m_resourceBarTex->getSize().x, m_size.y));
	m_resourceBarTex->render({0, m_size.y}, Vector2<Sint32>(curr, m_size.y));
}
