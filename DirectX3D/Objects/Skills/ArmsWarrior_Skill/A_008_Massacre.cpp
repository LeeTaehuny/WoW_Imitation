#include "Framework.h"
#include "A_008_Massacre.h"

A_008_Massacre::A_008_Massacre()
{
	// 선행 스킬
	prevSkills.push_back("A_006_FueledbyViolence");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/ArmsWarrior/08_Massacre.png");
}

A_008_Massacre::~A_008_Massacre()
{
	SAFE_DEL(icon);
}

void A_008_Massacre::UseSkill()
{
	// 공격력 20% 증가
	owner->GetStat().damage *= 1.2f;
}
