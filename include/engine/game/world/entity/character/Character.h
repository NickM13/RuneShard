#pragma once

#include "..\Entity.h"

class Character : public Entity
{
public:
	Character() {};
	Character(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);
	~Character() {};

	virtual void move(Vector3<GLfloat> p_direction);
	virtual void turn(Vector3<GLfloat> p_rotation);

	virtual Vector3<GLfloat> getRotation() {return m_rotation;}

	virtual void input();
	virtual void render();

protected:

};
