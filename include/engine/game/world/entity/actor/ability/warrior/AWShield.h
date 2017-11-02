#pragma once
#include "..\Ability.h"

class AWShield : public AbilityHold {
protected:
	void pressAction();
	void releaseAction();
	void updateAction();
public:
	AWShield(Sint32 p_casterId);
};
