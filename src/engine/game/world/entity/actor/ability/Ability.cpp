#include "engine\game\world\entity\actor\ability\Ability.h"

Ability::Ability(Sint32 p_casterId) {
	m_casterId = p_casterId;
	m_lastUse = 0;
}
void Ability::pressAction() {

}
void Ability::releaseAction() {

}
void Ability::updateAction() {

}
void Ability::press() {
	if(isAvailable()) {
		pressAction();
		m_lastUse = glfwGetTime();
	}
}
void Ability::release() {
	if(isAvailable()) {
		releaseAction();
		m_lastUse = glfwGetTime();
	}
}
void Ability::update() {

}



AbilityHold::AbilityHold(Sint32 p_casterId) : Ability(p_casterId) {
	m_isActive = false;
}
void AbilityHold::press() {
	if(isAvailable()) {
		pressAction();
		m_lastUse = glfwGetTime();
		m_isActive = true;
	}
}
void AbilityHold::release() {
	if(m_isActive) {
		releaseAction();
		m_lastUse = glfwGetTime();
		m_isActive = false;
	}
}
void AbilityHold::update() {
	if(m_isActive) {
		updateAction();
	}
}



AbilityCharge::AbilityCharge(Sint32 p_casterId) : AbilityHold(p_casterId) {
	
}
void AbilityCharge::press() {
	if(isAvailable()) {
		pressAction();
		m_lastUse = glfwGetTime();
		m_isActive = true;
	}
}
void AbilityCharge::release() {
	if(m_isActive) {
		releaseAction();
		m_lastUse = glfwGetTime();
		m_isActive = false;
	}
}
void AbilityCharge::update() {
	if(m_isActive) {

	}
}
