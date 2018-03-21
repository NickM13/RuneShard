#pragma once
#include "..\Ability.h"

class AWSwordSwing : public AbilityBasic {
protected:
	void pressAction();
	void releaseAction();
	void updateAction();
public:
	AWSwordSwing(Sint32 p_casterId);
};
