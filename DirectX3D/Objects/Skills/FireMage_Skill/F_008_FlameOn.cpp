#include "Framework.h"
#include "F_008_FlameOn.h"
#include "F_002_FireBlast.h"

F_008_FlameOn::F_008_FlameOn()
{
	skillName = "F_008_FlameOn";

	// 선행 스킬
	prevSkills.push_back("F_006_SurgingBlaze");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/08_FlameOn.png");
}

F_008_FlameOn::~F_008_FlameOn()
{
	SAFE_DEL(icon);
}

void F_008_FlameOn::UseSkill()
{
	// 화염작렬의 쿨타임 2초 감소
	vector<SkillBase*> tempSkills = owner->GetSkillList();

	for (SkillBase* skill : tempSkills)
	{
		// 002 스킬인 경우
		if (F_002_FireBlast* tmpSkill = dynamic_cast<F_002_FireBlast*>(skill))
		{
			// 쿨타임 2.0초 감소
			tmpSkill->SetCooltime(tmpSkill->GetCooltime() - 2.0f);
		}
	}
}
