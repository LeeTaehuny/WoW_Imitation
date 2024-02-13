#include "Framework.h"
#include "A_005_SharpenedBlades.h"

A_005_SharpenedBlades::A_005_SharpenedBlades()
{
	// 선행 스킬
	prevSkills.push_back("A_003_MartialProwess");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/ArmsWarrior/05_SharpenedBlades.png");
}

A_005_SharpenedBlades::~A_005_SharpenedBlades()
{
	SAFE_DEL(icon);
}

void A_005_SharpenedBlades::UseSkill()
{
	// 공격력 15% 증가
	owner->GetStat().damage *= 1.15;
	// 방어력 15% 증가
	owner->GetStat().defence *= 1.15;
}
