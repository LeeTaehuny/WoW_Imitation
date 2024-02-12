#pragma once
class P_004_Ardent_Defender : public ActiveSkill
{
public:
	P_004_Ardent_Defender();
	~P_004_Ardent_Defender();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

private:
	float Max_runTime;
	float runTime;

};