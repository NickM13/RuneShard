#include "engine\game\world\camera\Camera.h"
#include "engine\game\debug\DebugUI.h"

Camera::Camera() {
	m_followActor = 0;
	m_boomDistance = m_tBoomDistance = 10;
	m_position = m_tPosition = {};
	m_velocity = {};
	m_acceleration = {40, 40};
	m_rotation = m_tRotation = {};
	m_hud = new HUD();
	m_hud->addComponent((new HUDResourceBar("HEALTHBAR"))
		->setStatusType(HUDResourceBar::HEALTH))
		->setPosition({-100, 0});
}

void Camera::followActor(Actor *p_actor) {
	m_followActor = p_actor;
	setPosition(m_followActor->getEyePos(), true);
	m_velocity = {};
	setRotation(m_followActor->getRotation(), true);
	m_hud->init(m_followActor);
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
	m_tRotation.x = min(90, max(-90, m_tRotation.x));
}
void Camera::addRotation(Vector3<GLfloat> p_rotation, bool p_hardset) {
	setRotation(m_tRotation + p_rotation, p_hardset);
}

void Camera::input() {
	if(m_followActor != nullptr) {
		if(GKey::keyDown(GLFW_KEY_W)) m_followActor->addMovement(Actor::FORWARD);
		if(GKey::keyDown(GLFW_KEY_A)) m_followActor->addMovement(Actor::LEFT);
		if(GKey::keyDown(GLFW_KEY_S)) m_followActor->addMovement(Actor::BACK);
		if(GKey::keyDown(GLFW_KEY_D)) m_followActor->addMovement(Actor::RIGHT);
		if(GKey::keyPressed(GLFW_KEY_SPACE)) m_followActor->jump();

		m_followActor->abilityInput();
	}
	else {
		Vector3<GLfloat> _dir;
		if(GKey::keyDown(GLFW_KEY_W)) {
			_dir.x += (Math::sind(m_tRotation.y));
			_dir.z -= (Math::cosd(m_tRotation.y));
		}
		if(GKey::keyDown(GLFW_KEY_A)) {
			_dir.x -= (Math::cosd(m_tRotation.y));
			_dir.z -= (Math::sind(m_tRotation.y));
		}
		if(GKey::keyDown(GLFW_KEY_S)) {
			_dir.x -= (Math::sind(m_tRotation.y));
			_dir.z += (Math::cosd(m_tRotation.y));
		}
		if(GKey::keyDown(GLFW_KEY_D)) {
			_dir.x += (Math::cosd(m_tRotation.y));
			_dir.z += (Math::sind(m_tRotation.y));
		}
		m_velocity = _dir * m_acceleration.x;
		m_velocity.y = 0;
		if(GKey::keyDown(GLFW_KEY_SPACE)) {
			m_velocity.y += m_acceleration.y;
		}
		if(GKey::keyDown(GLFW_KEY_LEFT_SHIFT)) {
			m_velocity.y -= m_acceleration.y;
		}
	}

	m_tBoomDistance -= GMouse::getScroll() / 4.f;
	if(m_tBoomDistance < MIN_BOOM) m_tBoomDistance = MIN_BOOM;
	if(m_tBoomDistance > MAX_BOOM) m_tBoomDistance = MAX_BOOM;

	m_hud->input();
}

void Camera::update(WorldData& p_worldData, GLfloat p_deltaTime) {
	if(m_followActor != nullptr) {
		m_position = m_tPosition = m_followActor->getEyePos();
		m_position.y += 0.5f;
	}
	else {
		m_tPosition = m_tPosition + m_velocity * p_deltaTime;
		m_position = m_position + Math::smoothChangeVec3(m_position, m_tPosition, 20.f, p_deltaTime);
	}
	
	// Keeps rotation from flipping at 0° or 360°
	while(abs(m_rotation.y - m_tRotation.y) > 180) {
		if(m_rotation.y > m_tRotation.y)
			m_rotation.y -= 360;
		else
			m_rotation.y += 360;
	}
	m_rotation = m_rotation + Math::smoothChangeVec3(m_rotation, m_tRotation, 10.f, p_deltaTime);

	if(m_followActor != nullptr) {
		m_followActor->setRotation(m_tRotation);

		GLdouble _near = 0;
		Sint8 _face = 0;
		m_boomDistance += Math::smoothChange(m_boomDistance, m_tBoomDistance, 4.f, p_deltaTime);
		if(p_worldData.castBox(m_position - _camSize / 2, _camSize, Math::computeDirection(m_rotation) * m_boomDistance * -1, _near, _face))
			m_boomDistance *= _near;

		m_followActor->abilityUpdate();
	}

	m_hud->update(p_deltaTime);
}

void Camera::render2d() {
	//m_hud->render();
}

void Camera::useRotation() {
	glRotatef(m_rotation.x, 1, 0, 0);
	glRotatef(m_rotation.y, 0, 1, 0);
	glRotatef(m_rotation.z, 0, 0, 1);
}

void Camera::useView() {
	if(m_followActor != nullptr)
		glTranslatef(0, 0, -m_boomDistance);
	useRotation();
	glTranslatef(-(m_position.x), -(m_position.y), -(m_position.z));
}
