#pragma once
class P_009_Eye_Of_Tyr : public ActiveSkill
{
public:
	P_009_Eye_Of_Tyr();
	~P_009_Eye_Of_Tyr();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

private:
	BlendState* blendState[2];
	DepthStencilState* depthState[2];

	Quad* donut;
	CH_Base_ver2* targetCharcter;

	float Max_animStart = 0.45f;
	float animStart = 0;
};