#include "Framework.h"
#include "P_004_Ardent_Defender.h"

P_004_Ardent_Defender::P_004_Ardent_Defender()
{
	skillName = "P_004_Ardent_Defender";

	/*
	스킬의 효과

	8초동안 자신이 받는 모든 피해를 20% 만큼 감소시킴
	(방어력 2배로 대체)

	해당 스킬이 활성화 되어 있는 상태에서 죽음에 이르는 피해를 입는다면,
	죽지 않고 최대 생명력의 20%로 현재 체력이 바뀐다. (보류)
	*/

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
	owner->GetStat().defence *= 2;
}