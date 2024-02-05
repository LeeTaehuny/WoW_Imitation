#pragma once
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

	virtual void NonTarget() override;
	virtual void Target() override;

	// 즉발성 형식의 타겟팅 스킬인 경우
	void vong();
	// 투사체 형식의 타겟팅 스킬인 경우
	void wing();

	// 적 세팅
	virtual void SetEnemy(Collider* enemy) { this->enemy = enemy; }

protected:
	// 적의 콜라이더 정보
	Collider* enemy;

	// 자기 자신과 적의 방향 정보를 기록함
	Vector3 velocity;

	// 투사체라면 날아가는 속도를 지정 (생성자로 스킬 생성시 재조정 필요)
	float FlyingSpeed = 10;
	Type type;

};