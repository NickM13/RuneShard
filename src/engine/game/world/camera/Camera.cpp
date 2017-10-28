#include "engine\game\world\camera\Camera.h"
#include "engine\game\debug\DebugUI.h"

Camera::Camera() {
	m_followActor = 0;
	m_boomDistance = m_tBoomDistance = 10;
}

void Camera::followActor(Actor *p_actor) {
	m_followActor = p_actor;
	setPosition(m_followActor->getEyePos(), true);
	setRotation(m_followActor->getRotation(), true);
}

void Camera::setPosition(Vector3<GLfloat> p_position, bool p_hardset) {
	m_followActor->setPosition(p_position);
	if(p_hardset) m_position = m_followActor->getPosition();
}
void Camera::addPosition(Vector3<GLfloat> p_position, bool p_hardset) {
	setPosition(m_followActor->getPosition() + p_position, p_hardset);
}
void Camera::setRotation(Vector3<GLfloat> p_rotation, bool p_hardset) {
	m_tRotation = p_rotation;
	if(p_hardset) m_position = m_tRotation;
}
void Camera::addRotation(Vector3<GLfloat> p_rotation, bool p_hardset) {
	setRotation(m_tRotation + p_rotation, p_hardset);
}

void Camera::input() {
	Vector3<GLfloat> _dir;
	if(GKey::keyDown(GLFW_KEY_W)) {
		_dir.x += (Math::sind(m_followActor->getRotation().y));
		_dir.z -= (Math::cosd(m_followActor->getRotation().y));
	}
	if(GKey::keyDown(GLFW_KEY_A)) {
		_dir.x -= (Math::cosd(m_followActor->getRotation().y));
		_dir.z -= (Math::sind(m_followActor->getRotation().y));
	}
	if(GKey::keyDown(GLFW_KEY_S)) {
		_dir.x -= (Math::sind(m_followActor->getRotation().y));
		_dir.z += (Math::cosd(m_followActor->getRotation().y));
	}
	if(GKey::keyDown(GLFW_KEY_D)) {
		_dir.x += (Math::cosd(m_followActor->getRotation().y));
		_dir.z += (Math::sind(m_followActor->getRotation().y));
	}
	m_followActor->move(_dir);
	if(GKey::keyPressed(GLFW_KEY_SPACE))
		m_followActor->jump();
	if(GMouse::mousePressed(GLFW_MOUSE_BUTTON_LEFT))
		m_followActor->abilityLeft();
	if(GMouse::mousePressed(GLFW_MOUSE_BUTTON_RIGHT))
		m_followActor->abilityRight();
	if(GKey::keyPressed(GLFW_KEY_1))
		m_followActor->ability1();
	if(GKey::keyPressed(GLFW_KEY_2))
		m_followActor->ability2();
	if(GKey::keyPressed(GLFW_KEY_LEFT_SHIFT))
		m_followActor->abilityDash();

	m_tBoomDistance -= GMouse::getScroll() / 2.f;
	if(m_tBoomDistance < MIN_BOOM) m_tBoomDistance = MIN_BOOM;
	if(m_tBoomDistance > MAX_BOOM) m_tBoomDistance = MAX_BOOM;
}

void Camera::update(WorldData& p_worldData, GLfloat p_deltaTime) {
	// Keeps rotation from flipping at 0° or 360°
	while(abs(m_rotation.y - m_tRotation.y) > 180) {
		if(m_rotation.y > m_tRotation.y)
			m_rotation.y -= 360;
		else
			m_rotation.y += 360;
	}

	m_position = m_position + Math::smoothChangeVec3(m_position, m_followActor->getEyePos(), 5.f, p_deltaTime);
	m_rotation = m_rotation + Math::smoothChangeVec3(m_rotation, m_tRotation, 10.f, p_deltaTime);
	m_followActor->setRotation(m_rotation);

	GLdouble _near = 0;
	Sint8 _face = 0;
	m_boomDistance += Math::smoothChange(m_boomDistance, m_tBoomDistance, 4.f, p_deltaTime);
	if(p_worldData.castBox(m_position - _camSize / 2, _camSize, Math::computeDirection(m_rotation) * m_boomDistance * -1, _near, _face))
		m_boomDistance *= _near;
}

void Camera::useRotation() {
	glRotatef(m_rotation.x, 1, 0, 0);
	glRotatef(m_rotation.y, 0, 1, 0);
	glRotatef(m_rotation.z, 0, 0, 1);
}

void Camera::useView() {
	glTranslatef(0, 0, -m_boomDistance);
	useRotation();
	glTranslatef(-(m_position.x), -(m_position.y), -(m_position.z));
}
