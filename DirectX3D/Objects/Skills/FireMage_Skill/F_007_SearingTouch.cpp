#include "Framework.h"
#include "F_007_SearingTouch.h"

F_007_SearingTouch::F_007_SearingTouch()
{
	skillName = "F_007_SearingTouch";

	// 선행 스킬
	prevSkills.push_back("F_004_Scorch");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/07_SearingTouch.png");
}

F_007_SearingTouch::~F_007_SearingTouch()
{
	SAFE_DEL(icon);
}

void F_007_SearingTouch::UseSkill()
{
	// 플레이어의 기본 데미지 증가 20%
	owner->GetStat().damage *= 1.2f;
}
