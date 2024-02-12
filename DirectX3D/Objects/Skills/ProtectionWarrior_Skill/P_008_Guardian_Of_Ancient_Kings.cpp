#include "Framework.h"
#include "P_008_Guardian_Of_Ancient_Kings.h"

P_008_Guardian_Of_Ancient_Kings::P_008_Guardian_Of_Ancient_Kings()
	: ActiveSkill(SkillType::Target)
{
	/*
	스킬의 효과

	8초동안 자신이 받는 모든 피해를 50%만큼 감소시킴
	*/

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 100.0f;

		// 쿨타임 설정 (기본적으로 5분)
		MAX_delay = 5.0f;
		coolTime = MAX_delay;

		Max_runTime = 8.0f;
		runTime = Max_runTime;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 불명 : 0.5%
		usingType = NON_Data;
	}
	
	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/008.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "P_006_Bulwark_Of_Order";
	prevSkills[1] = "P_007_Blessing_of_Spellwarding";
}

P_008_Guardian_Of_Ancient_Kings::~P_008_Guardian_Of_Ancient_Kings()
{

	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
}

void P_008_Guardian_Of_Ancient_Kings::Update()
{
	if (isRun)
	{
		runTime -= DELTA;
		if (runTime <= 0)
		{
			runTime = Max_runTime;
			isRun = false;
		}

		owner->GetStat().defence += 50;
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void P_008_Guardian_Of_Ancient_Kings::Render()
{
}

void P_008_Guardian_Of_Ancient_Kings::UseSkill()
{
	if (isCooldown) nullptr;

	isCooldown = true;
	isRun = true;
}