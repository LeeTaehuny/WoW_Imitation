#pragma once
class P_010_Moment_Of_Glory : public PassiveSkill
{
public:
	P_010_Moment_Of_Glory();
	~P_010_Moment_Of_Glory();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};