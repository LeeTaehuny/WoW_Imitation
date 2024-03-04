#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class F_003_Pyrotechnics : public PassiveSkill
{
public:
	F_003_Pyrotechnics();
	virtual ~F_003_Pyrotechnics() override;

	virtual void UseSkill() override;

private:
};

