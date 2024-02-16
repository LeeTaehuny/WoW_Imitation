#include "Framework.h"
#include "H_005_Censure.h"

H_005_Censure::H_005_Censure()
{
	skillName = "H_005_Censure";

	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/005.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "H_004_Holy_Word_Chastise";
}

H_005_Censure::~H_005_Censure()
{
	delete icon;
}

void H_005_Censure::UseSkill()
{
	owner->GetStat().damage *= 1.2f;
}