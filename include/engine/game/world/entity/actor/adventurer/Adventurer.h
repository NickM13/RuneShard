#pragma once
#include "..\Actor.h"

class Adventurer : public Actor {
public:
	Adventurer(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);
};
