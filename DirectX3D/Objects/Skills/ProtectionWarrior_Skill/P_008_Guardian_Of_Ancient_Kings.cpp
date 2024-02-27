#include "Framework.h"
#include "P_008_Guardian_Of_Ancient_Kings.h"

P_008_Guardian_Of_Ancient_Kings::P_008_Guardian_Of_Ancient_Kings()
{
	skillName = "P_008_Guardian_Of_Ancient_Kings";

	/*
	스킬의 효과

	8초동안 자신이 받는 모든 피해를 50%만큼 감소시킴
	(방어력 5배 증가로 대체)
	*/
	
	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/008.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "P_007_Blessing_of_Spellwarding";
}

P_008_Guardian_Of_Ancient_Kings::~P_008_Guardian_Of_Ancient_Kings()
{
	delete icon;
}

void P_008_Guardian_Of_Ancient_Kings::Update()
{
	
}

void P_008_Guardian_Of_Ancient_Kings::Render()
{
}

void P_008_Guardian_Of_Ancient_Kings::UseSkill()
{
	owner->GetStat().defence *= 1.2;
}