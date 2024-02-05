#pragma once
class SkillBase
{
public:
	enum SkillType
	{
		TARGET,
		NONTARGET,
	};

public:
	SkillBase(SkillType skill);
	virtual ~SkillBase();

	// 업데이트로 호출, 생성자 매개변수로 받은 값에 따라 업데이트 함수가 다름
	void SkillUpdate();
	void Render();

	// 논타겟일 경우 이쪽 사용
	virtual void NonTarget() = 0;
	// 타겟 스킬일 경우 이쪽 사용
	virtual void Target() = 0;

	// 스킬 발동
	void SkillFire(Vector3 pos);
	// 타겟스킬 클래스에서 사용하기 위한 타겟된 적의 정보를 받아오는 함수
	virtual void SetEnemy(Collider* enemy) = 0;

protected:
	// 타겟, 논타겟 판별용
	SkillType skill;

	// 본인의 콜라이더
	Collider* myCollider;

	// 스킬 파티클
	Particle* particle;
	Quad* skillIcon;

};