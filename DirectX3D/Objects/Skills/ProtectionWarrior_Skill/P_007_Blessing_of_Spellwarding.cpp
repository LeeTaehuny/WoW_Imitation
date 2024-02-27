#include "Framework.h"
#include "P_007_Blessing_of_Spellwarding.h"

P_007_Blessing_of_Spellwarding::P_007_Blessing_of_Spellwarding()
{
	skillName = "P_007_Blessing_of_Spellwarding";

	/*
	스킬의 효과

	대상 파티원에게 10초동안 모든 마법 피해 및 해로운 효과의 면역을 줍니다.
	(방어력 2배 증가로 대체)
	*/

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/007.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "P_004_Ardent_Defender";
}

P_007_Blessing_of_Spellwarding::~P_007_Blessing_of_Spellwarding()
{
	delete icon;
}

void P_007_Blessing_of_Spellwarding::Update()
{

}

void P_007_Blessing_of_Spellwarding::Render()
{
	
}

void P_007_Blessing_of_Spellwarding::UseSkill()
{
	owner->GetStat().defence *= 1.2f;
}