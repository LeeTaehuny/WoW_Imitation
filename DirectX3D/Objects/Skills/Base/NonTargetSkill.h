#pragma once
class NonTargetSkill : public SkillBase
{
public:
	NonTargetSkill();
	~NonTargetSkill();

	virtual void NonTarget() override;
	virtual void Target() = 0;

};

