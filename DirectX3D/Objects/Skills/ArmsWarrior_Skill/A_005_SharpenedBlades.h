#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class A_005_SharpenedBlades : public PassiveSkill
{
public:
	A_005_SharpenedBlades();
	virtual ~A_005_SharpenedBlades() override;

	virtual void UseSkill() override;

private:
};

