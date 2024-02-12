#pragma once
class P_008_Guardian_Of_Ancient_Kings : public ActiveSkill
{
public:
	P_008_Guardian_Of_Ancient_Kings();
	~P_008_Guardian_Of_Ancient_Kings();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

private:
	float Max_runTime;
	float runTime;
};