#pragma once

#include "engine\utils\OpenGL.h"
#include "engine\utils\variable\datatype\Macros.h"
#include "engine\utils\variable\datatype\Vector3.h"
#include "engine\utils\variable\manager\VoxelModelManager.h"

#include "engine\sfx\Sound.h"
#include "..\data\WorldData.h"

#include <vector>

class Entity {
protected:
	Vector3<GLfloat> m_position;
	Vector3<GLfloat> m_size;
	Vector3<GLfloat> m_rotation;
	Vector3<GLfloat> m_acceleration;
	Vector3<GLfloat> m_velocity;
	bool m_noClip;
	bool m_onGround;
	GLfloat m_health, m_maxHealth;
	VoxelModel* m_voxelModel = 0;
	bool m_exists = true;
public:
	Entity();
	Entity(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);
	~Entity();

	void setModel(VoxelModel* p_voxelModel);

	void push(Vector3<GLfloat> p_direction);
	virtual void move(Vector3<GLfloat> p_direction);
	virtual void turn(Vector3<GLfloat> p_rotation);
	void setPosition(Vector3<GLfloat> p_position) { m_position = p_position; }

	Vector3<GLfloat> getPosition() const { return m_position; };
	Vector3<GLfloat> getCorner() const { return m_position + Vector3<GLfloat>(-m_size.x / 2, 0, -m_size.z / 2); };
	Vector3<GLfloat> getCenter() const { return m_position + Vector3<GLfloat>(0, m_size.y / 2, 0); };
	Vector3<GLfloat> getSize() const { return m_size; };
	Vector3<GLfloat> getRotation() const { return m_rotation; };
	Vector3<GLfloat> getVelocity() const { return m_velocity; };
	Vector3<GLfloat> getLookVector() { return Math::computeDirection({m_rotation.x, m_rotation.y, m_rotation.z}); };
	Vector3<GLfloat> getEyePos() { return Vector3<GLfloat>(m_position.x, m_position.y + m_size.y - 0.15f, m_position.z); }

	virtual void input();
	virtual void update(WorldData p_world, GLfloat p_deltaTime);
	virtual void render();
	virtual void renderShadow();
	void useView();

	bool exists() const { return m_exists; }
};
