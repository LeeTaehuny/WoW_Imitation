#include "Framework.h"
#include "M_006_Streamline.h"

M_006_Streamline::M_006_Streamline()
{
	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/006.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "M_003_Rapid_Fire";
}

M_006_Streamline::~M_006_Streamline()
{
	delete icon;
}

void M_006_Streamline::UseSkill()
{
	owner->GetStat().damage *= 1.5f;
}