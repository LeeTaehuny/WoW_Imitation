#include "Framework.h"
#include "A_003_MartialProwess.h"
#include "A_001_MortalStrike.h"
#include "A_002_Overpower.h"

A_003_MartialProwess::A_003_MartialProwess()
{
	skillName = "A_003_MartialProwess";

	// 선행 스킬
	prevSkills.push_back("A_002_Overpower");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/ArmsWarrior/03_MartialProwess.png");
}

A_003_MartialProwess::~A_003_MartialProwess()
{
	SAFE_DEL(icon);
}

void A_003_MartialProwess::UseSkill()
{
	vector<SkillBase*> tempSkills = owner->GetSkillList();

	for (SkillBase* skill : tempSkills)
	{
		// 001 스킬인 경우
		if (A_001_MortalStrike* tmpSkill = dynamic_cast<A_001_MortalStrike*>(skill))
		{
			// 쿨타임 0.5초 감소
			tmpSkill->SetCooltime(tmpSkill->GetCooltime() - 0.5f);
			// 데미지 10% 증가
			tmpSkill->SetDamage(0.1f);
		}
		// 002 스킬인 경우
		else if (A_002_Overpower* tmpSkill = dynamic_cast<A_002_Overpower*>(skill))
		{
			// 쿨타임 0.5초 감소
			tmpSkill->SetCooltime(tmpSkill->GetCooltime() - 0.5f);
			// 데미지 10% 증가
			tmpSkill->SetDamage(0.1f);
		}
	}
}