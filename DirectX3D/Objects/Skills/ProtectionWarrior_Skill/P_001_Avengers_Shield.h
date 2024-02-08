#pragma once
class P_001_Avengers_Shield : public ActiveSkill
{
public:
	P_001_Avengers_Shield();
	~P_001_Avengers_Shield();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() {}
	virtual void UseSkill(Collider* targetCollider) override;
	virtual void UseSkill(Vector3 direction) {}

	// 스킬 사용 함수, 이 함수를 호출하면 스킬이 발동함
	//virtual void UseSkill(Vector3 pos) override;

	// 이 클래스만의 에너미 세팅
	void SetEnemy(Collider* enemy) { this->three[0] = enemy; }

	// 임펙트 함수
	void Impact();

private:
	// 사정 거리를 판별하기 위한 콜라이더
	Collider* Yad;

	// 날아갈 방패의 모델
	Model* shielD;

	// 공격 타겟 3마리 지정용 함수, 콜라이더를 저장해 놓을 것임
	vector<Collider*> three;
	
	// 날아간 방패가 적이랑 부딪힌 횟수
	int impaction_count = 0;
};