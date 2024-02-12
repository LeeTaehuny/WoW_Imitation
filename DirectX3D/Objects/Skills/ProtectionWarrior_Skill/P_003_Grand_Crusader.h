#pragma once
class P_003_Grand_Crusader : public PassiveSkill
{
public:
	P_003_Grand_Crusader();
	~P_003_Grand_Crusader();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};