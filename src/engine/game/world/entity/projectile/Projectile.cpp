#include "engine\game\world\entity\projectile\Projectile.h"

void Projectile::inputProjectile() {

}
void Projectile::input() {

}
void Projectile::updatePhysics(GLfloat p_updateTime) {
	m_bVelocity = m_velocity + m_tVelocity;
}
void Projectile::updateActorCollision() {

}
void Projectile::updateWorldCollision(WorldData &p_world) {

}
void Projectile::updateProjectile() {

}
void Projectile::updateMovement() {

}
void Projectile::update(WorldData &p_world, GLfloat p_updateTime) {
	updatePhysics(p_updateTime);
	updateActorCollision();
	updateWorldCollision(p_world);
	updateProjectile();
	updateMovement();
}
void Projectile::renderProjectile() {

}
void Projectile::render() {

}

std::vector<Projectile*> MProjectile::m_projectileList;
Uint32 MProjectile::m_actorCount;
