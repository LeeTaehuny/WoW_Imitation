#pragma once
class P_024_Guardian_Of_Ancient_Kings : public ActiveSkill
{
public:
	P_024_Guardian_Of_Ancient_Kings();
	~P_024_Guardian_Of_Ancient_Kings();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};