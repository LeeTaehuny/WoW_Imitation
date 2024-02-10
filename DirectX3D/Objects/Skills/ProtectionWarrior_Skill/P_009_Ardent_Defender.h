#pragma once
class P_009_Ardent_Defender : public ActiveSkill
{
public:
	P_009_Ardent_Defender();
	~P_009_Ardent_Defender();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};