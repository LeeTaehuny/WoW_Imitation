#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class F_007_SearingTouch : public PassiveSkill
{
public:
	F_007_SearingTouch();
	virtual ~F_007_SearingTouch() override;

	virtual void UseSkill() override;

private:
};

