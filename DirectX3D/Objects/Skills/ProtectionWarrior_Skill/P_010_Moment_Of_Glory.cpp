#include "Framework.h"
#include "P_010_Moment_Of_Glory.h"

P_010_Moment_Of_Glory::P_010_Moment_Of_Glory()
{
	skillName = "P_010_Moment_Of_Glory";

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/010.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "P_008_Guardian_Of_Ancient_Kings";
}

P_010_Moment_Of_Glory::~P_010_Moment_Of_Glory()
{
	delete icon;
}

void P_010_Moment_Of_Glory::Update()
{

}

void P_010_Moment_Of_Glory::Render()
{

}

void P_010_Moment_Of_Glory::UseSkill()
{
	// 전체 체력의 30% 회복
	owner->GetStat().maxHp += owner->GetStat().maxHp * 0.3f;
}