#include "Framework.h"
#include "P_003_Grand_Crusader.h"

P_003_Grand_Crusader::P_003_Grand_Crusader()
{
	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/003.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "P_001_Avengers_Shield";
}

P_003_Grand_Crusader::~P_003_Grand_Crusader()
{
	delete icon;
}

void P_003_Grand_Crusader::Update()
{
}

void P_003_Grand_Crusader::Render()
{
}

void P_003_Grand_Crusader::UseSkill()
{
	// 공격력 20% 증가로 대체
	owner->GetStat().damage *= 1.2f;
}