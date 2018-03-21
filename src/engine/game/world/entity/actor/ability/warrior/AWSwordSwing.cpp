#include "engine\game\world\entity\actor\ability\warrior\AWSwordSwing.h"
#include "engine\game\world\entity\actor\Actor.h"

void AWSwordSwing::pressAction() {

}
void AWSwordSwing::releaseAction() {

}
void AWSwordSwing::updateAction() {

}
AWSwordSwing::AWSwordSwing(Sint32 p_casterId) : AbilityBasic(p_casterId) {
	m_abilityName = "Warrior_Sword_Swing";
	m_cooldown = 0;
}
