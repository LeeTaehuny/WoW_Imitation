#include "Framework.h"
#include "F_003_Pyrotechnics.h"

F_003_Pyrotechnics::F_003_Pyrotechnics()
{
	// 선행 스킬
	prevSkills.push_back("F_001_Pyroblast");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/03_Pyrotechnics.png");
}

F_003_Pyrotechnics::~F_003_Pyrotechnics()
{
	SAFE_DEL(icon);
}

void F_003_Pyrotechnics::UseSkill()
{
	// 공격력 10% 증가
	owner->GetStat().damage *= 1.1f;
}
