#include "Framework.h"
#include "P_010_Moment_Of_Glory.h"

P_010_Moment_Of_Glory::P_010_Moment_Of_Glory()
{
	skillName = "P_010_Moment_Of_Glory";

	/*
	스킬의 효과

	15초 동안 입힌 모든 피해의 25%에 해당하는 피해 흡수 보호막을 생성함
	(체력 즉시 회복으로 대체)

	응징의 방패의 공격력 20% 상승 및 재사용시간 75%만큼 감소 (삭제)
	*/

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
	// 전체 체력의 3할 회복
	owner->GetStat().maxHp += owner->GetStat().maxHp * 0.3f;
}