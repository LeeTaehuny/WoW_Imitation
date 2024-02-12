#pragma once
class H_005_Censure : public PassiveSkill
{
public:
	H_005_Censure();
	~H_005_Censure();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};