#pragma once
#include "SkillBase.h"

// 스킬의 타입을 구분하기 위한 열거형
enum class SkillType
{
	Target,		// 타겟 스킬
	NonTarget,	// 논타겟 스킬
};

enum UseType
{
	monster_Data,
	character_Data,
	collider_Data,
	NON_Data,
};

class ActiveSkill : public SkillBase
{
public:
	ActiveSkill(SkillType type);
	virtual ~ActiveSkill() override;

	virtual void Update() override;
	virtual void Render() override;


	UseType GetUsing() { return usingType; }
	int GetRequiredMp() { return requiredMp; }

	bool GetIsCooldown() { return isCooldown; }
	int GetrequiredMp() { return requiredMp; }

	float GetCoolTime() { return coolTime; }

private:
	void TargetUpdate();
	void NonTargetUpdate();

protected:
	// 쿨타임을 감소시키기 위한 함수
	void Cooldown();

	// 실제 충돌 연산을 진행할 콜라이더
	Collider* myCollider;
	Collider* hitCollider;

	// 쿨타임
	float MAX_delay;
	float coolTime;

	// 쿨타임 중인지를 판별하기 위한 변수 (T: 쿨타임, F:사용가능)
	bool isCooldown;
	// 스킬이 사용중(실행 중)인지 판별하기 위한 변수
	bool isRun;

	// 스킬의 타입을 저장하기 위한 변수
	SkillType skillType;
	// 유싱 타입을 저장하기 위한 변수
	UseType usingType;

	// 방향을 저장하기 위한 변수
	Vector3 direction;
	// 스킬의 속도를 저장하기 위한 변수
	float speed;

	// 타겟의 콜라이더 정보
	Collider* target;
	// 타격에 성공했는지 여부
	bool impact;

	// 스킬 데미지 양
	float skillDamage;

	// 사용 마나량
	int requiredMp;
};