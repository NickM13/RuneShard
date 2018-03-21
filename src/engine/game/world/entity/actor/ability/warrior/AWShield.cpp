#include "engine\game\world\entity\actor\ability\warrior\AWShield.h"
#include "engine\game\world\entity\actor\Actor.h"

void AWShield::pressAction() {

}
void AWShield::releaseAction() {

}
void AWShield::updateAction() {
}
AWShield::AWShield(Sint32 p_casterId) : AbilityHold(p_casterId) {
	m_abilityName = "Warrior_Shield";
	m_cooldown = 0;
}
