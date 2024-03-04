#pragma once
class Lich_007_Defile : public Lich_000_Base
{
public:
	Lich_007_Defile(Boss_LichKing* lich);
	~Lich_007_Defile();

	virtual void Update() override;
	virtual void Render() override;
	// 스킬 사용에 쓰기 위한 함수
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

private:
	Quad* particle;
	Collider* hitCollider;

	CH_Base_ver2* characterData;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];

	float Max_runTime = 30.0f;
	float runTime = Max_runTime;

	float Max_tickTime = 0.5f;
	float tickTime = Max_tickTime;

	float vaUl = 0.01f;

	vector<CH_Base_ver2*> conh;
};