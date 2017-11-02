#include "engine\game\world\entity\actor\ability\warrior\AWShield.h"
#include "engine\game\world\entity\actor\Actor.h"

void AWShield::pressAction() {
	std::cout << "shield" << std::endl;
}
void AWShield::releaseAction() {
	std::cout << "shield release" << std::endl;
}
void AWShield::updateAction() {
	std::cout << "charge update" << std::endl;
}
AWShield::AWShield(Sint32 p_casterId) : AbilityHold(p_casterId) {
	m_abilityName = "Warrior_Shield";
	m_cooldown = 0;
}
