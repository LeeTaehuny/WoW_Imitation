#pragma once
class H_003_Guardian_Spirit : public ActiveSkill
{
public:
	H_003_Guardian_Spirit();
	~H_003_Guardian_Spirit();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase) override;

private:
	// 실제 수호령을 담당할 변수
	Quad* spirit;
	BlendState* blendState[2];
	DepthStencilState* depthState[2];

	// 스킬을 적용시킬 타겟
	CH_Base_ver2* healingTarget;

	float Max_runTime;
	float runTime;

	float Max_healingTick;
	float healingTick;
};