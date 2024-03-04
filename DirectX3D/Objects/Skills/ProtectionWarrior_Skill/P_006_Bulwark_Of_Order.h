#pragma once
class P_006_Bulwark_Of_Order : public PassiveSkill
{
public:
	P_006_Bulwark_Of_Order();
	~P_006_Bulwark_Of_Order();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};