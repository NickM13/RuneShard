#pragma once
#include "..\Ability.h"

class AMFireball : public Ability {
protected:
	void abilityAction();
public:
	AMFireball(Sint32 p_casterId);
};
