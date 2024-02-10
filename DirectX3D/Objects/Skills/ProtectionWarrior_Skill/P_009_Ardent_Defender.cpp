#include "Framework.h"
#include "P_009_Ardent_Defender.h"

P_009_Ardent_Defender::P_009_Ardent_Defender() : ActiveSkill(SkillType::Target)
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
		skillDamage = 100.0f;

		// 쿨타임 설정
		MAX_delay = 120.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/009.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "005";
}

P_009_Ardent_Defender::~P_009_Ardent_Defender()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
}

void P_009_Ardent_Defender::Update()
{
	if (owner == nullptr) return;

	if (isRun)
	{
		isRun = false;
	}

	ActiveSkill::Cooldown();
}

void P_009_Ardent_Defender::Render()
{
}

void P_009_Ardent_Defender::UseSkill()
{
	isCooldown = true;
	isRun = true;
}