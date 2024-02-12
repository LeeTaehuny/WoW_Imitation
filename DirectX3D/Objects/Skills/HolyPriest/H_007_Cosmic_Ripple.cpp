#include "Framework.h"
#include "H_007_Cosmic_Ripple.h"

H_007_Cosmic_Ripple::H_007_Cosmic_Ripple()
{
	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/007.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "H_002_Holy_Word_Sanctify";
}

H_007_Cosmic_Ripple::~H_007_Cosmic_Ripple()
{
	delete icon;
}

void H_007_Cosmic_Ripple::UseSkill()
{
	// 방어력 20% 상승
	owner->GetStat().defence *= 1.2f;
}