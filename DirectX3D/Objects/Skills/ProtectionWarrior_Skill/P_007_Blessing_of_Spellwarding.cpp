#include "Framework.h"
#include "P_007_Blessing_of_Spellwarding.h"

P_007_Blessing_of_Spellwarding::P_007_Blessing_of_Spellwarding()
{
	skillName = "P_007_Blessing_of_Spellwarding";

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