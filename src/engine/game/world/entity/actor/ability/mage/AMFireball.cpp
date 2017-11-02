#include "engine\game\world\entity\actor\ability\mage\AMFireball.h"
#include "engine\game\world\entity\actor\Actor.h"

void AMFireball::abilityAction() {

}
AMFireball::AMFireball(Sint32 p_casterId) : Ability(p_casterId) {
	m_abilityName = "Mage_Fireball";
	m_cooldown = 0;
}
