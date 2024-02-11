#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class F_008_FlameOn : public PassiveSkill
{
public:
	F_008_FlameOn();
	virtual ~F_008_FlameOn() override;

	virtual void UseSkill() override;

private:
};

