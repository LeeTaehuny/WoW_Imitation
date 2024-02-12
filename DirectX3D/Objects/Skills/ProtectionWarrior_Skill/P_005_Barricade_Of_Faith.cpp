#include "Framework.h"
#include "P_005_Barricade_Of_Faith.h"

P_005_Barricade_Of_Faith::P_005_Barricade_Of_Faith()
{
	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/005.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "P_003_Grand_Crusader";
}

P_005_Barricade_Of_Faith::~P_005_Barricade_Of_Faith()
{
	delete icon;
}

void P_005_Barricade_Of_Faith::Update()
{
}

void P_005_Barricade_Of_Faith::Render()
{
}

void P_005_Barricade_Of_Faith::UseSkill()
{
	// 방어력 10퍼센트 증가로 대체
	owner->GetStat().defence *= 1.1f;
}