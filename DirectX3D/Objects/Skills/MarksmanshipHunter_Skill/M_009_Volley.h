#pragma once
class M_009_Volley : public ActiveSkill
{
public:
	M_009_Volley();
	~M_009_Volley();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

	// 스킬 발동부분을 함수로 제작
	void Using(int imto);

private:
	MonsterBase* targetMonster;

	vector<Quad*> monsterTecture;
	vector<Arrow*> Arrows;
	vector<Collider*> targetCollider;
	vector<Vector3> directions;
	vector<float> velocity;
	vector<int> startTiming;

	int ThisNumber = -1;

	float Max_runTime = 6;
	float runTime = 0;

	float Max_tickDamageTime = 0.5f;
	float tickDamageTime = 0;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];
	float Max_animStart = 0.35f;
	float animStart = 0;

	bool isOne_sound = false;
};