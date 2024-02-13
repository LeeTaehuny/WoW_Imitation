#include "Framework.h"
#include "A_006_FueledbyViolence.h"
#include "Objects/Character_/ArmsWarrior_in.h"

A_006_FueledbyViolence::A_006_FueledbyViolence()
{
	// 선행 스킬
	prevSkills.push_back("A_003_MartialProwess");
	prevSkills.push_back("A_004_DiebytheSword");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/ArmsWarrior/06_FueledbyViolence.png");
}

A_006_FueledbyViolence::~A_006_FueledbyViolence()
{
	SAFE_DEL(icon);
}

void A_006_FueledbyViolence::UseSkill()
{
	// 생명력 흡수 On
	if (ArmsWarrior_in* warrior = dynamic_cast<ArmsWarrior_in*>(owner))
	{
		warrior->SetBuffLifeDrain(true);
	}
}
