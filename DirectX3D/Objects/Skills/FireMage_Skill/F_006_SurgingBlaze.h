#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class F_006_SurgingBlaze : public PassiveSkill
{
public:
	F_006_SurgingBlaze();
	virtual ~F_006_SurgingBlaze() override;

	virtual void UseSkill() override;

private:
};

