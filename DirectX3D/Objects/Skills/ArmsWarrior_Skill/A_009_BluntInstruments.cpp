#include "Framework.h"
#include "A_009_BluntInstruments.h"
#include "A_007_ColossusSmash.h"

A_009_BluntInstruments::A_009_BluntInstruments()
{
	skillName = "A_009_BluntInstruments";

	// 선행 스킬
	prevSkills.push_back("A_007_ColossusSmash");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/ArmsWarrior/09_BluntInstruments.png");
}

A_009_BluntInstruments::~A_009_BluntInstruments()
{
	SAFE_DEL(icon);
}

void A_009_BluntInstruments::UseSkill()
{
	vector<SkillBase*> tempSkills = owner->GetSkillList();

	for (SkillBase* skill : tempSkills)
	{
		// 007 스킬인 경우
		if (A_007_ColossusSmash* tmpSkill = dynamic_cast<A_007_ColossusSmash*>(skill))
		{
			// 쿨타임 10초 감소
			tmpSkill->SetCooltime(tmpSkill->GetCooltime() - 10.0f);
			// 데미지 30% 증가
			tmpSkill->SetDamage(0.3f);
		}
	}
}
