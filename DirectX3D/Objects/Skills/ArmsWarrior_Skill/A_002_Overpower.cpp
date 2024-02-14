﻿#include "Framework.h"
#include "A_002_Overpower.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Character_/ArmsWarrior_in.h"

A_002_Overpower::A_002_Overpower() : ActiveSkill(SkillType::NonTarget)
{
	// 충돌 판정용 콜라이더
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 쿨타임 설정 (12초)
	MAX_delay = 12.0f;
	coolTime = MAX_delay;

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	startEdge = new Transform();
	endEdge = new Transform();

	trail = new Trail(L"Textures/Effect/warriorTrail.png", startEdge, endEdge, 5, 10.0f);

	// 소모 마냐량
	requiredMp = 30;

	// 선행 스킬
	prevSkills.push_back("A_001_MortalStrike");

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/ArmsWarrior/02_Overpower.png");

	// 공격 지속 시간 1.5초
	duration = 1.5f;
	curTime = 0.0f;

	additiveDamage = 1.0f;

	usingType = UseType::NON_Data;
}

A_002_Overpower::~A_002_Overpower()
{
	SAFE_DEL(myCollider);
	SAFE_DEL(startEdge);
	SAFE_DEL(endEdge);
	SAFE_DEL(trail);
	SAFE_DEL(icon);
}

void A_002_Overpower::Update()
{
	if (isRun)
	{
		startEdge->Pos() = myCollider->GlobalPos() + myCollider->Forward() * 2;
		endEdge->Pos() = myCollider->GlobalPos() + myCollider->Back();

		curTime += DELTA;

		if (curTime >= duration)
		{
			curTime = 0.0f;
			isRun = false;
			myCollider->SetActive(false);
		}

		// myCollider와의 충돌 체크
		vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
		vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
		vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();

		for (MonsterBase* monster : cols1)
		{
			if (find(hit.begin(), hit.end(), monster) == hit.end())
			{
				if (myCollider->IsCollision(monster->GetCollider()))
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);
					hit.push_back(monster);
				}
			}
		}

		for (MonsterBase* monster : cols2)
		{
			if (find(hit.begin(), hit.end(), monster) == hit.end())
			{
				if (myCollider->IsCollision(monster->GetCollider()))
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);
					hit.push_back(monster);
				}
			}
		}

		for (MonsterBase* monster : cols3)
		{
			if (find(hit.begin(), hit.end(), monster) == hit.end())
			{
				if (myCollider->IsCollision(monster->GetCollider()))
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);
					hit.push_back(monster);
				}
			}
		}

		myCollider->UpdateWorld();
	}
	else
	{
		startEdge->Pos() = owner->GetWeapon()->GlobalPos();
		endEdge->Pos() = owner->GetWeapon()->GlobalPos();

		hit.clear();
	}

	if (isCooldown)
	{
		Cooldown();
	}

	startEdge->UpdateWorld();
	endEdge->UpdateWorld();
	trail->Update();
}

void A_002_Overpower::Render()
{
	myCollider->Render();

	if (isRun)
		trail->Render();
}

void A_002_Overpower::UseSkill()
{
	if (owner->GetWeapon() == nullptr) return;

	if (ArmsWarrior_in* player = dynamic_cast<ArmsWarrior_in*>(owner))
	{
		if (!isRun && !isCooldown)
		{
			if (player->GetState() == player->State::ATTACK1) return;

			myCollider->SetActive(true);
			owner->GetWeapon()->ClearHit();
			myCollider->SetParent(owner->GetWeapon());
			myCollider->UpdateWorld();

			player->SetState(player->State::ATTACK1);
			owner->GetInstancing()->PlayClip(owner->GetIndex(), 3);

			isRun = true;
			isCooldown = true;

			Init();
		}
	}
}

void A_002_Overpower::Init()
{
	// 스킬 데미지
	int temp = owner->GetStat().damage;
	skillDamage = temp * 3.0f * additiveDamage;
}
