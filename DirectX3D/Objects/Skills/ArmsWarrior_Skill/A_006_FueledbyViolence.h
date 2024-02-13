#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class A_006_FueledbyViolence : public PassiveSkill
{
public:
	A_006_FueledbyViolence();
	virtual ~A_006_FueledbyViolence() override;

	virtual void UseSkill() override;

private:
};

