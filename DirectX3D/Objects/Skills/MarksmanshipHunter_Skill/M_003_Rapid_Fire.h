#pragma once
class M_003_Rapid_Fire : public ActiveSkill
{
public:
	M_003_Rapid_Fire();
	~M_003_Rapid_Fire();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

	void tack(int imto);

private:
	MonsterBase* monster;

	vector<Arrow*> seven; // 화살 모델을 컨트롤 하기 위한 트랜스폼 변수
	vector<Collider*> it_me_Mario; // 실제로 날아갈 변수
	vector<float> deleyTime; // 화살이 이정 시간 지나는 것을 체크하기 위한 변수
	float Max_time = 0.2f;
	vector<int> startTiming; // 화살이 시작 될 타이밍을 재기 위한 변수
	vector<bool> skillonoff;
	vector<Quad*> effectTexture;

	BlendState* blendState[2];
	DepthStencilState* depthState[2];

	float Max_animStart = 0.35f;
	float animStart = 0;
};