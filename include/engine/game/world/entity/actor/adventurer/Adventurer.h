#pragma once
#include "..\Actor.h"

class Adventurer : public Actor {
protected:

public:
	Adventurer(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);

	virtual void abilityDash();
	virtual void abilityRight();
	virtual void abilityLeft();
	virtual void ability1();
	virtual void ability2();
};
