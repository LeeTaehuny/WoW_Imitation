﻿#include "Framework.h"
#include "F_004_Scorch.h"

F_004_Scorch::F_004_Scorch() : ActiveSkill(SkillType::Target)
{
	skillName = "F_004_Scorch";

	// 쿨타임 설정 (1.5초)
	MAX_delay = 1.5f;
	coolTime = MAX_delay;

	// 선행 스킬
	prevSkills.push_back("F_002_FireBlast");

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	// 이펙트 추가
	hitParticleSystem = new ParticleSystem("TextData/Particles/Fire/targetFire.fx");

	// 소모 마냐량
	requiredMp = 10;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/04_Scorch.png");

	// 스킬 지연 발사
	delayTime = 0.0f;
	MAX_delayAnim = 1.5f;

	additiveDamage = 1.0f;

	usingType = UseType::monster_Data;
}

F_004_Scorch::~F_004_Scorch()
{
	SAFE_DEL(hitParticleSystem);
	SAFE_DEL(icon);
}

void F_004_Scorch::Update()
{
	if (owner->GetWeapon() == nullptr) return;

	if (delayTime < MAX_delayAnim && isRun)
	{
		delayTime += DELTA;
	}
	else
	{
		hitParticleSystem->Update();

		if (isCooldown)
		{
			Cooldown();
		}

		if (isRun)
		{
			// 해당 충돌체의 주인 찾기
			vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
			vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
			vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();
			vector<MonsterBase*> cols4 = MONSTER->GetVAlkier();
			vector<MonsterBase*> cols5 = MONSTER->GetIceBall();
			MonsterBase* cols6 = MONSTER->GetLichKing();

			for (MonsterBase* monster : cols1)
			{
				if (monster->GetCollider() == target)
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);

					hitParticleSystem->Play(target->GlobalPos());
					isRun = false;
					return;
				}
			}

			for (MonsterBase* monster : cols2)
			{
				if (monster->GetCollider() == target)
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);

					hitParticleSystem->Play(target->GlobalPos());
					isRun = false;
					return;
				}
			}

			for (MonsterBase* monster : cols3)
			{
				if (monster->GetCollider() == target)
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);

					hitParticleSystem->Play(target->GlobalPos());
					isRun = false;
					return;
				}
			}

			for (MonsterBase* monster : cols4)
			{
				if (monster->GetCollider() == target)
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);

					hitParticleSystem->Play(target->GlobalPos());
					isRun = false;
					return;
				}
			}

			for (MonsterBase* monster : cols5)
			{
				if (monster->GetCollider() == target)
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);

					hitParticleSystem->Play(target->GlobalPos());
					isRun = false;
					return;
				}
			}

			if (cols6)
			{
				if (cols6->GetCollider() == target)
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					cols6->Hit(skillDamage);

					hitParticleSystem->Play(target->GlobalPos());
					isRun = false;
					return;
				}
			}
		}
	}
}

void F_004_Scorch::Render()
{
	hitParticleSystem->Render();
}

void F_004_Scorch::UseSkill(MonsterBase* monsterbase)
{
	if (owner->GetWeapon() == nullptr) return;

	if (monsterbase == nullptr) return;

	if (FireMage_in* player = dynamic_cast<FireMage_in*>(owner))
	{
		if (!isRun && !isCooldown)
		{
			if (player->GetState() == player->State::ATTACK1) return;

			target = monsterbase->GetCollider();

			player->SetState(player->State::ATTACK1);
			owner->GetInstancing()->PlayClip(owner->GetIndex(), 2, 1.0f);

			isRun = true;
			isCooldown = true;

			delayTime = 0.0f;

			owner->GetStat().mp -= requiredMp;

			if (owner->GetStat().mp < 0)
			{
				owner->GetStat().mp = 0;
			}

			Init();
		}
	}
}

void F_004_Scorch::Init()
{
	// 스킬 데미지 설정
	int temp = owner->GetStat().damage;

	if (FireMage_in* mage = dynamic_cast<FireMage_in*>(owner))
	{
		if (mage->GetDoubleDamage())
		{
			skillDamage = 2 * temp * additiveDamage;
		}
		else
		{
			skillDamage = temp * additiveDamage;
		}
	}
}
