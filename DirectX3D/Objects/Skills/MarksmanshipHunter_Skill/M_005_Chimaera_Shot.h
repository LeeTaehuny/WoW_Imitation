#pragma once
class M_005_Chimaera_Shot : public ActiveSkill
{
public:
	M_005_Chimaera_Shot();
	~M_005_Chimaera_Shot();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

private:
	Collider* Yad;

	MonsterBase* mon1;
	MonsterBase* mon2;

	Collider* col1;
	Collider* col2;

	Arrow* tol1;
	Arrow* tol2;

	Quad* effectTexture1;
	Quad* effectTexture2;
	BlendState* blendState[2];
	DepthStencilState* depthState[2];

	float Max_animStart = 0.35f;
	float animStart = 0;
};