#include "Framework.h"
#include "M_002_Crack_Shot.h"

M_002_Crack_Shot::M_002_Crack_Shot()
{
	skillName = "M_002_Crack_Shot";

	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/002.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "M_001_Aimed_Shot";
}

M_002_Crack_Shot::~M_002_Crack_Shot()
{
	delete icon;
}

void M_002_Crack_Shot::UseSkill()
{
	owner->GetStat().mp += 10 * DELTA;
}