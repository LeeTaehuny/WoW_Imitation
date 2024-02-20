#include "Framework.h"
#include "M_007_Focused_Aim.h"

M_007_Focused_Aim::M_007_Focused_Aim()
{
	skillName = "M_007_Focused_Aim";

	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/007.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "M_004_Lone_Wolf";
	prevSkills[1] = "M_005_Chimaera_Shot";
}

M_007_Focused_Aim::~M_007_Focused_Aim()
{
	delete icon;
}

void M_007_Focused_Aim::UseSkill()
{
	owner->GetStat().damage *= 1.5f;
}