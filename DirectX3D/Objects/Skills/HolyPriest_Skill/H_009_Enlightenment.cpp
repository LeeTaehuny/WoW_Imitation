#include "Framework.h"
#include "H_009_Enlightenment.h"

H_009_Enlightenment::H_009_Enlightenment()
{
	skillName = "H_009_Enlightenment";

	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/009.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "H_005_Censure";
}

H_009_Enlightenment::~H_009_Enlightenment()
{
	delete icon;
}

void H_009_Enlightenment::UseSkill()
{
	owner->GetStat().mp += 5 * DELTA;
}