#pragma once
#include "engine\utils\Math.h"
#include "engine\utils\OpenGL.h"
#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector3.h"
#include "engine\utils\variable\manager\VoxelModelManager.h"
#include "engine\utils\global\GGameState.h"

#include "engine\sfx\Sound.h"
#include "..\data\WorldData.h"

#include <vector>

class Entity {
protected:
	Vector3<GLfloat> m_position;
	Vector3<GLfloat> m_size;
	Vector3<GLfloat> m_rotation;
	Vector3<GLfloat> m_acceleration;
	Vector3<GLfloat> m_velocity, m_tVelocity;
	GLfloat m_weight;
	GLfloat m_bounciness;
	GLfloat m_health, m_maxHealth;
	bool m_noClip = false;
	bool m_onGround = false;
	bool m_collided = false;
	bool m_exists = true;

	virtual void updatePhysics(WorldData p_world, GLfloat p_deltaTime);
	virtual void updateCollision(WorldData p_world, GLfloat p_deltaTime);

	virtual void renderModel();
	virtual void renderOutline();
	virtual void renderShadow();
public:
	Entity();
	Entity(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);
	~Entity();

	void push(Vector3<GLfloat> p_direction);
	virtual void move(Vector3<GLfloat> p_direction);
	virtual void turn(Vector3<GLfloat> p_rotation);
	void setPosition(Vector3<GLfloat> p_position) { m_position = p_position; }
	void addPosition(Vector3<GLfloat> p_position) { m_position = m_position + p_position; }
	void setRotation(Vector3<GLfloat> p_rotation) { m_rotation = p_rotation; }
	void addRotation(Vector3<GLfloat> p_rotation) { m_rotation = m_rotation + p_rotation; }

	Vector3<GLfloat> getPosition() const { return m_position; };
	Vector3<GLfloat> getCorner() const { return m_position + Vector3<GLfloat>(-m_size.x / 2, 0, -m_size.z / 2); };
	Vector3<GLfloat> getCenter() const { return m_position + Vector3<GLfloat>(0, m_size.y / 2, 0); };
	Vector3<GLfloat> getSize() const { return m_size; };
	Vector3<GLfloat> getRotation() const { return m_rotation; };
	Vector3<GLfloat> getVelocity() const { return m_velocity; };
	Vector3<GLfloat> getLookVector() { return Math::computeDirection({m_rotation.x, m_rotation.y, m_rotation.z}); };
	Vector3<GLfloat> getEyePos() { return Vector3<GLfloat>(m_position.x, m_position.y + m_size.y + 0.15f, m_position.z); }

	void input();
	virtual void update(WorldData p_world, GLfloat p_deltaTime);
	void render();

	bool exists() const { return m_exists; }
};
