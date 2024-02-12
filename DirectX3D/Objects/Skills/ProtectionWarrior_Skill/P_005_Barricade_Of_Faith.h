#pragma once
class P_005_Barricade_Of_Faith : public PassiveSkill
{
public:
	P_005_Barricade_Of_Faith();
	~P_005_Barricade_Of_Faith();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};