#include "Framework.h"
#include "P_004_Ardent_Defender.h"

P_004_Ardent_Defender::P_004_Ardent_Defender()
{
	skillName = "P_004_Ardent_Defender";

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/004.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "P_003_Grand_Crusader";
}

P_004_Ardent_Defender::~P_004_Ardent_Defender()
{
	delete icon;
}

void P_004_Ardent_Defender::Update()
{
	
}

void P_004_Ardent_Defender::Render()
{
}

void P_004_Ardent_Defender::UseSkill()
{
	// 방어력을 10% 증가
	owner->GetStat().defence *= 1.1f;
}