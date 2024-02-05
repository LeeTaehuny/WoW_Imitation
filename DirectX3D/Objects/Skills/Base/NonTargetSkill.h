#pragma once
class NonTargetSkill : public SkillBase
{
public:
	NonTargetSkill();
	virtual ~NonTargetSkill();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void UseSkill() = 0;

	void NonTarget();

};