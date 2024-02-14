#pragma once
class M_010_Wailing_Arrow : public ActiveSkill
{
public:
	M_010_Wailing_Arrow();
	~M_010_Wailing_Arrow();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

private:

	MonsterBase* monsterTarget;
	Arrow* arrow;
	Quad* arrowTexture;

	ParticleSystem* particle;
	int nujucIndex = 0;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	float Max_animStart = 0.35f;
	float animStart = 0;
};