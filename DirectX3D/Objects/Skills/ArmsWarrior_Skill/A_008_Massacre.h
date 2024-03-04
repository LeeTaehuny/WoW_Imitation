#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class A_008_Massacre : public PassiveSkill
{
public:
	A_008_Massacre();
	virtual ~A_008_Massacre() override;

	virtual void UseSkill() override;

private:
};

