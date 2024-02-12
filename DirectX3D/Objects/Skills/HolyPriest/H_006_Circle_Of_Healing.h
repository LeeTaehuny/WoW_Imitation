#pragma once
class H_006_Circle_Of_Healing : public ActiveSkill
{
public:
	H_006_Circle_Of_Healing();
	~H_006_Circle_Of_Healing();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase) override;

private:
	Quad* magic_circle;
	BlendState* blendState[2];

	// 스킬을 적용시킬 타겟
	vector<CH_Base_ver2*> healingTargets;
	vector<ParticleSystem*> particles;
	vector<int> isOne;

	float Max_animStart = 0.9f;
	float animStart = 0;
};