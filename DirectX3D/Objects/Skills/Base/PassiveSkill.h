#pragma once
#include "SkillBase.h"

class PassiveSkill : public SkillBase
{
public:
	PassiveSkill();
	virtual ~PassiveSkill() override;

	virtual void Update() override;
	virtual void Render() override;
};

