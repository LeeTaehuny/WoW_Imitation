#pragma once
class M_001_Aimed_Shot : public ActiveSkill
{
public:
	M_001_Aimed_Shot();
	~M_001_Aimed_Shot();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

private:
	Model* arrow;
	MonsterBase* targetMonster;
	Quad* effectTexture;
	BlendState* blendState[2];
	DepthStencilState* depthState[2];

	float Max_animStart = 0.35f;
	float animStart = 0;
};