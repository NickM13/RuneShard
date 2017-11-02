#pragma once
#include "..\Ability.h"

class AWCharge : public AbilityHold {
protected:
	void pressAction();
	void releaseAction();
	void updateAction();
public:
	AWCharge(Sint32 p_casterId);
};
