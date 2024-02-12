#include "Framework.h"
#include "P_004_Ardent_Defender.h"

P_004_Ardent_Defender::P_004_Ardent_Defender() : ActiveSkill(SkillType::Target)
{
	/*
	스킬의 효과

	8초동안 자신이 받는 모든 피해를 20% 만큼 감소시킴

	해당 스킬이 활성화 되어 있는 상태에서 죽음에 이르는 피해를 입는다면,
	죽지 않고 최대 생명력의 20%로 현재 체력이 바뀐다.
	*/

	// 기본 생성 요소
	{
		// 스킬 속도 (필요 없음)
		speed = 0.0f;

		// 스킬 데미지 (회복으로 넣어야 함)
		skillDamage = 0.0f;

		// 쿨타임 설정
		MAX_delay = 120.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		Max_runTime = 8.0f;
		runTime = Max_runTime;

		// // 마나 소모 불명 : 약 1.0%
		usingType = NON_Data;
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/004.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "P_003_Grand_Crusader";
}

P_004_Ardent_Defender::~P_004_Ardent_Defender()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
}

void P_004_Ardent_Defender::Update()
{
	if (isRun)
	{
		runTime -= DELTA;
		if (runTime <= 0)
		{
			runTime = Max_runTime;
			isRun = false;
		}

		owner->GetStat().defence += 20;
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void P_004_Ardent_Defender::Render()
{
}

void P_004_Ardent_Defender::UseSkill()
{
	if (isCooldown) nullptr;

	skillDamage = owner->GetStat().damage;
	isCooldown = true;
	isRun = true;
}