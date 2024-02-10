#include "Framework.h"
#include "P_024_Guardian_Of_Ancient_Kings.h"

P_024_Guardian_Of_Ancient_Kings::P_024_Guardian_Of_Ancient_Kings() : ActiveSkill(SkillType::Target)
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

		// 쿨타임 설정 (5초)
		MAX_delay = 5.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;
	}
	
	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/0024.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "013";
	prevSkills[1] = "014";
}

P_024_Guardian_Of_Ancient_Kings::~P_024_Guardian_Of_Ancient_Kings()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
}

void P_024_Guardian_Of_Ancient_Kings::Update()
{
}

void P_024_Guardian_Of_Ancient_Kings::Render()
{
}

void P_024_Guardian_Of_Ancient_Kings::UseSkill()
{
}
