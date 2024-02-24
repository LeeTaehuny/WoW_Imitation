#include "Framework.h"
#include "H_004_Holy_Word_Chastise.h"

H_004_Holy_Word_Chastise::H_004_Holy_Word_Chastise() : ActiveSkill(SkillType::Target)
{
	skillName = "H_004_Holy_Word_Chastise";

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본은 (60초)
		MAX_delay = 5.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 : 2.0%
		requiredMp = 20;
		usingType = monster_Data;
	}

	particle = new ParticleSystem("TextData/Particles/Priests/Skill04.fx");

	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/004.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "H_001_Holy_Word_Serenity";
}

H_004_Holy_Word_Chastise::~H_004_Holy_Word_Chastise()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete particle;
	delete targetMonster;
}

void H_004_Holy_Word_Chastise::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;
		//if (!targetMonster->GetCollider()->Active())
		//{
		//	isOne = 0;
		//	isRun = false;
		//	return;
		//}

		if (isOne == 0)
		{
			particle->Play(Vector3());
			targetMonster->Hit(skillDamage);
			isOne++;
		}

		if (particle->IsPlay())
		{
			Vector3 lll = targetMonster->GetCollider()->GlobalPos();
			lll.y += targetMonster->GetCollider()->GlobalScale().y * 2;

			particle->SetPos(lll);
			particle->Update();
		}
		else 
		{
			isOne = 0;
			isRun = false;
		}
	}
	

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void H_004_Holy_Word_Chastise::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		particle->Render();
	}
}

void H_004_Holy_Word_Chastise::UseSkill(MonsterBase* monsterbase)
{
	if (isCooldown || monsterbase == nullptr ||
		owner->GetStat().mp < requiredMp ||
		!owner->GetWeapon()) return;

	skillDamage = owner->GetStat().damage * 2.45f;
	owner->GetStat().mp -= requiredMp;

	if (HolyPriest_in* c = dynamic_cast<HolyPriest_in*>(owner))
	{
		c->SetState(HolyPriest_in::State::ATTACK1);
	}

	animStart = 0;
	targetMonster = monsterbase;
	isRun = true;
	isCooldown = true;
}