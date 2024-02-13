#pragma once
class M_008_Multi_Shot : public ActiveSkill
{
public:
	M_008_Multi_Shot();
	~M_008_Multi_Shot();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

	void Using(int imto);

private:
	vector<MonsterBase*> monsters;
	vector<Quad*> monsterTecture;
	vector<Transform*> targetArrows;
	vector<Collider*> targetCollider;
	vector<int> startTiming;

	int ThisNumber = 0;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	float Max_animStart = 0.35f;
	float animStart = 0;
};