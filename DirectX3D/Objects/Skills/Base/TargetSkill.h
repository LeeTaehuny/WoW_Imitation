#pragma once

//  FlyingSpeed 속도 조절 필요
class TargetSkill : public SkillBase
{
public:
	enum Type
	{
		AA, // 즉발성
		BB, // 투사체
	};

public:
	TargetSkill(Type type);
	virtual ~TargetSkill();

	//virtual void Update() = 0;
	//virtual void Render() = 0;
	//virtual void UseSkill(Vector3 pos) = 0;

	// 콜라이더를 날리는 함수
	// 즉발성인가 투사체인가 판별도 알아서 해줍니다.
	void Target();
	// 즉발성 형식의 타겟팅 스킬인 경우
	void vong();
	// 투사체 형식의 타겟팅 스킬인 경우
	void wing();

	// 적 세팅
	void SetEnemy(Collider* enemy) { this->enemy = enemy; }

protected:
	// 적의 콜라이더 정보
	Collider* enemy;

	// 자기 자신과 적의 방향 정보를 기록함
	Vector3 velocity;

	// 투사체라면 날아가는 속도를 지정 (생성자로 스킬 생성시 재조정 필요)
	float FlyingSpeed = 10;
	// 즉발성인가 투사체인가를 판별하기 위한 변수
	Type type;
	// 충돌 했는지를 판별하는 함수
	bool impact = false;

};