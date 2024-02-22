#include "Framework.h"
#include "A_004_DiebytheSword.h"
#include "Objects/Character_/ArmsWarrior_in.h"

A_004_DiebytheSword::A_004_DiebytheSword() : ActiveSkill(SkillType::Target)
{
	skillName = "A_004_DiebytheSword";

	// 지속 시간 설정
	curTime = 0.0f;
	MAX_duration = 8.0f;

	// 쿨타임 설정 (2분)
	MAX_delay = 120.0f;
	coolTime = MAX_delay;

	// 선행 스킬
	prevSkills.push_back("A_002_Overpower");

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	particle = new ParticleSystem("TextData/Particles/Warrior/defenceBuff.fx");

	// 소모 마나량
	requiredMp = 100.0f;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/ArmsWarrior/04_DiebytheSword.png");

	usingType = UseType::NON_Data;
}

A_004_DiebytheSword::~A_004_DiebytheSword()
{
	SAFE_DEL(particle);
	SAFE_DEL(icon);
}

void A_004_DiebytheSword::Update()
{
	if (owner->GetWeapon() == nullptr) return;

	if (isRun)
	{
		particle->SetPos(owner->GetCollider()->GlobalPos());
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

		// 방어력 증가 버프 종료
		if (ArmsWarrior_in* warrior = dynamic_cast<ArmsWarrior_in*>(owner))
		{
			warrior->SetBuffDefence(false);
		}
	}


	if (isCooldown)
	{
		Cooldown();
	}
}

void A_004_DiebytheSword::Render()
{
	if (particle->IsActive())
	{
		particle->Render();
	}
}

void A_004_DiebytheSword::UseSkill()
{
	if (!isRun && !isCooldown)
	{
		isRun = true;
		isCooldown = true;

		// 방어력 버프 On
		if (ArmsWarrior_in* warrior = dynamic_cast<ArmsWarrior_in*>(owner))
		{
			warrior->SetBuffDefence(true);
		}

		owner->GetStat().mp -= requiredMp;

		if (owner->GetStat().mp < 0)
		{
			owner->GetStat().mp = 0;
		}

		particle->SetScale(Vector3(2.0f, 2.0f, 2.0f));
		particle->Play(owner->GetCollider()->GlobalPos());
	}
}
