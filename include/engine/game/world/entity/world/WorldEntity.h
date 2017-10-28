#pragma once

#include "..\Entity.h"

class WorldEntity : public Entity
{
public:
	WorldEntity(Vector3<GLfloat> p_pos, Vector3<GLfloat> p_size, VoxelModel* p_model)
	{
		m_position = {p_pos.x + p_size.x / 2, p_pos.y + 1, p_pos.z + p_size.z / 2};
		m_size = p_size;
	}
	void input()
	{

	}
	void update(GLfloat p_updateTime)
	{

	}
	void render()
	{
		Entity::render();
	}
};
