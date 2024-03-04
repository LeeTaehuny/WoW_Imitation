#include "Framework.h"
#include "M_004_Lone_Wolf.h"

M_004_Lone_Wolf::M_004_Lone_Wolf()
{
	skillName = "M_004_Lone_Wolf";

	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/004.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "M_001_Aimed_Shot";
}

M_004_Lone_Wolf::~M_004_Lone_Wolf()
{
	delete icon;
}

void M_004_Lone_Wolf::UseSkill()
{
	owner->GetStat().damage *= 1.2f;
}