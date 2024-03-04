#pragma once
class P_001_Avengers_Shield : public ActiveSkill
{
public:
	P_001_Avengers_Shield();
	~P_001_Avengers_Shield();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

	// 사거리 정보를 받아오기 위한 겟터
	Collider* Getyad() { return Yad; }

private:
	// 사정 거리를 판별하기 위한 콜라이더
	Collider* Yad;

	// 날아갈 방패의 모델
	Model* shielD;

	// 공격 타겟 3마리 지정용 함수, 콜라이더를 저장해 놓을 것임
	vector<MonsterBase*> three;

	MonsterBase* targetMonster;

	Transform* startEdge;
	Transform* endEdge;
	Trail* trail;
	
	// 날아간 방패가 적이랑 부딪힌 횟수
	int impaction_count = 0;

	float Max_animStart = 0.45f;
	float animStart = 0;

	int onejacdong = 0;
};