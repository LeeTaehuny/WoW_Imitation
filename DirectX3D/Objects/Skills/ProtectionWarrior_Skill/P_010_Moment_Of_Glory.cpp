#include "Framework.h"
#include "P_010_Moment_Of_Glory.h"

P_010_Moment_Of_Glory::P_010_Moment_Of_Glory() : ActiveSkill(SkillType::Target)
{
	/*
	스킬의 효과

	15초 동안 입힌 모든 피해의 25%에 해당하는 피해 흡수 보호막을 생성함

	응징의 방패의 공격력 20% 상승 및 재사용시간 75%만큼 감소
	*/
	
	// 기본 생성 요소
	{
		// 스킬 속도 (필요 없음)
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 (기본은 90초)
		MAX_delay = 5.0f;
		coolTime = MAX_delay;

		maxRuntime = 15.0f;
		curRuntime = maxRuntime;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 불명 : 0.5%
		usingType = character_Data;
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/010.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "P_013_Bulwark_Of_Order";
	prevSkills[1] = "P_024_Guardian_Of_Ancient_Kings";
}

P_010_Moment_Of_Glory::~P_010_Moment_Of_Glory()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
}

void P_010_Moment_Of_Glory::Update()
{
	if (isRun)
	{
		curRuntime -= DELTA;
		if (curRuntime <= 0)
		{
			curRuntime = maxRuntime;
			isRun = false;
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void P_010_Moment_Of_Glory::Render()
{
}

void P_010_Moment_Of_Glory::UseSkill(CH_Base_ver2* chbase)
{
	if (chbase == nullptr) return;
	targetCharcter = chbase;

	skillDamage = owner->GetStat().damage;
	isRun = true;
	isCooldown = true;
}