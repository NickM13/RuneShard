#pragma once
#include "..\Adventurer.h"

class Warrior : public Adventurer {
protected:

public:
	Warrior(Vector3<GLfloat> p_position, Vector3<GLfloat> p_size, Vector3<GLfloat> p_rotation);

	virtual void abilityDash();
	virtual void abilityRight();
	virtual void abilityLeft();
	virtual void ability1();
	virtual void ability2();
};
