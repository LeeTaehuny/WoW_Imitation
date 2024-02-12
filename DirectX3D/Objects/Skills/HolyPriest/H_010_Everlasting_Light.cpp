#include "Framework.h"
#include "H_010_Everlasting_Light.h"

H_010_Everlasting_Light::H_010_Everlasting_Light()
{
	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/010.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "H_007_Cosmic_Ripple";
	prevSkills[1] = "H_008_Divine_Hymn";
}

H_010_Everlasting_Light::~H_010_Everlasting_Light()
{
	delete icon;
}

void H_010_Everlasting_Light::UseSkill()
{
	owner->GetStat().defence += 20;
}