#pragma once

#include "engine\utils\OpenGL.h"
#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector3.h"

#include "engine\sfx\Sound.h"

#include "engine\gfx\model\VoxelModel.h"

#include "..\data\WorldData.h"

#include <vector>

class Entity
{
public:
	Entity();
	Entity(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);
	~Entity();

	void setModel(VoxelModel* p_voxelModel);

	void setMoveSpeed(GLfloat p_speed);
	void setJumpHeight(GLfloat p_jumpHeight);

	void push(Vector3<GLfloat> p_direction);
	virtual void move(Vector3<GLfloat> p_direction);
	virtual void turn(Vector3<GLfloat> p_rotation);
	virtual void jump();

	virtual Vector3<GLfloat> getPosition() { return m_position; };
	virtual Vector3<GLfloat> getCorner() { return m_position + Vector3<GLfloat>(-m_size.x / 2, 0, -m_size.z / 2); };
	virtual Vector3<GLfloat> getCenter() { return m_position + Vector3<GLfloat>(0, m_size.y / 2, 0); };
	virtual Vector3<GLfloat> getSize() { return m_size; };
	virtual Vector3<GLfloat> getRotation() { return m_rotation; };
	virtual Vector3<GLfloat> getVelocity() { return m_velocity; };
	Vector3<GLfloat> getLookVector() { return Math::computeDirection({-m_rotation.x, m_rotation.y, m_rotation.z}); };
	Vector3<GLfloat> getEyePos() { return Vector3<GLfloat>(m_position.x, m_position.y + m_size.y - 0.15f, m_position.z); }

	virtual void input();
	virtual void update(WorldData p_world, GLfloat p_deltaTime);
	virtual void render();
	virtual void renderShadow();

	GLfloat getHealth() { return m_health; };
	GLfloat getMaxHealth() { return m_maxHealth; };
	void damage(GLfloat amt) { m_health -= amt; };

	void useView();
protected:
	Vector3<GLfloat> m_position;
	Vector3<GLfloat> m_size;
	Vector3<GLfloat> m_rotation;

	GLfloat m_speed;
	GLfloat m_jumpHeight;
	Uint8 m_airJumps = 0; // For double jumps
	Uint8 m_jumps;
	Vector3<GLfloat> m_acceleration;
	Vector3<GLfloat> m_velocity;

	std::vector<Entity> m_collidedEntities;

	bool m_noClip;
	bool m_onGround;

	VoxelModel* m_voxelModel = 0;

	Source m_soundJump;

	GLfloat m_maxHealth, m_health;
};
