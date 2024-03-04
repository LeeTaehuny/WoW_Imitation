#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class A_003_MartialProwess : public PassiveSkill
{
public:
	A_003_MartialProwess();
	virtual ~A_003_MartialProwess() override;

	virtual void UseSkill() override;

private:
};