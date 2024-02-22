#include "Framework.h"
#include "F_009_Combustion.h"
#include "Objects/Character_/FireMage_in.h"

F_009_Combustion::F_009_Combustion() : ActiveSkill(SkillType::Target)
{
	skillName = "F_009_Combustion";

	// 지속 시간 설정
	curTime = 0.0f;
	MAX_duration = 10.0f;

	// 쿨타임 설정 (2분)
	MAX_delay = 120.0f;
	coolTime = MAX_delay;

	// 선행 스킬
	prevSkills.push_back("F_008_FlameOn");

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	particle = new ParticleSystem("TextData/Particles/Fire/buffFire.fx");

	// 소모 마나량
	requiredMp = 100.0f;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/09_Combustion.png");

	usingType = UseType::NON_Data;
}

F_009_Combustion::~F_009_Combustion()
{
	SAFE_DEL(particle);
	SAFE_DEL(icon);
}

void F_009_Combustion::Update()
{
	if (owner->GetWeapon() == nullptr) return;

	if (isRun)
	{
		particle->SetPos(owner->GlobalPos());
		particle->Update();

		curTime += DELTA;

		if (curTime >= MAX_duration)
		{
			isRun = false;
			curTime = 0.0f;
		}
	}
	else
	{
		particle->Stop();

		// 2배 데미지 종료
		if (FireMage_in* mage = dynamic_cast<FireMage_in*>(owner))
		{
			mage->SetDoubleDamage(false);
		}
	}
	

	if (isCooldown)
	{
		Cooldown();
	}
}

void F_009_Combustion::Render()
{
	if (particle->IsActive())
	{
		particle->Render();
	}
}

void F_009_Combustion::UseSkill()
{
	if (!isRun && !isCooldown)
	{
		isRun = true;
		isCooldown = true;

		// TODO : 내 모든 데미지 * 2로 설정
		if (FireMage_in* mage = dynamic_cast<FireMage_in*>(owner))
		{
			mage->SetDoubleDamage(true);
		}

		owner->GetStat().mp -= requiredMp;

		if (owner->GetStat().mp < 0)
		{
			owner->GetStat().mp = 0;
		}
		
		particle->Play(owner->GlobalPos());
	}
}
