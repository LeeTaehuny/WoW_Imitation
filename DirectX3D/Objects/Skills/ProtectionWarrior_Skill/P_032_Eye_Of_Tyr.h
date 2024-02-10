#pragma once
class P_032_Eye_Of_Tyr : public ActiveSkill
{
public:
	P_032_Eye_Of_Tyr();
	~P_032_Eye_Of_Tyr();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

private:
	BlendState* blendState[2];
	DepthStencilState* depthState[2];

	Quad* donut;
	CH_Base_ver2* targetCharcter;
};