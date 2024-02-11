#include "Framework.h"
#include "F_006_SurgingBlaze.h"
#include "F_001_Pyroblast.h"
#include "F_002_FireBlast.h"

F_006_SurgingBlaze::F_006_SurgingBlaze()
{
	// 선행 스킬
	prevSkills.push_back("F_003_Pyrotechnics");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/06_SurgingBlaze.png");
}

F_006_SurgingBlaze::~F_006_SurgingBlaze()
{
	SAFE_DEL(icon);
}

void F_006_SurgingBlaze::UseSkill()
{
	vector<SkillBase*> tempSkills = owner->GetSkillList();

	for (SkillBase* skill : tempSkills)
	{
		// 001 스킬인 경우
		if (F_001_Pyroblast* tmpSkill = dynamic_cast<F_001_Pyroblast*>(skill))
		{
			// 쿨타임 0.5초 감소
			tmpSkill->SetCooltime(tmpSkill->GetCooltime() - 0.5f);
			// 데미지 10% 증가
			tmpSkill->SetDamage(tmpSkill->GetDamage() * 1.1f);
		}
		// 002 스킬인 경우
		else if (F_002_FireBlast* tmpSkill = dynamic_cast<F_002_FireBlast*>(skill))
		{
			// 쿨타임 0.5초 감소
			tmpSkill->SetCooltime(tmpSkill->GetCooltime() - 0.5f);
			// 데미지 10% 증가
			tmpSkill->SetDamage(tmpSkill->GetDamage() * 1.1f);
		}
	}
}
