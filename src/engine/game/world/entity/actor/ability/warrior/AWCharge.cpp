#include "engine\game\world\entity\actor\ability\warrior\AWCharge.h"
#include "engine\game\world\entity\actor\LActor.h"

void AWCharge::pressAction() {
	Actor* caster = MActor::getActor(m_casterId);
	caster->setSprinting(true);
}
void AWCharge::releaseAction() {
	Actor* caster = MActor::getActor(m_casterId);
	caster->setSprinting(false);
}
void AWCharge::updateAction() {
	Actor* caster = MActor::getActor(m_casterId);
	caster->setMovement(Actor::Direction::FORWARD);
	caster->damage(1);
}
AWCharge::AWCharge(Sint32 p_casterId) : AbilityHold(p_casterId) {
	m_abilityName = "Warrior_Charge";
	m_cooldown = 0;
}
