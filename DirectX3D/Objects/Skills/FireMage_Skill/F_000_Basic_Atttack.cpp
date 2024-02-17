#include "Framework.h"
#include "F_000_Basic_Atttack.h"

F_000_Basic_Atttack::F_000_Basic_Atttack() : ActiveSkill(SkillType::Target)
{
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 20.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 기본 공격 딜레이
		MAX_delay = 0.3f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// 마나 소모 : 0%
		usingType = monster_Data;
	}
	particle = new ParticleSystem("TextData/Particles/Fire/fireBall.fx");
}

F_000_Basic_Atttack::~F_000_Basic_Atttack()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete particle;
}

void F_000_Basic_Atttack::Update()
{
	if (isCooldown)
		ActiveSkill::Cooldown();

	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		direction = (targetMonster->GetCollider()->GlobalPos() - myCollider->GlobalPos()).GetNormalized();
		myCollider->Pos() += direction * speed * DELTA;
		myCollider->UpdateWorld();

		if (particle->IsPlay())
		{
			particle->SetPos(myCollider->GlobalPos());
			particle->Update();
		}
		else if (!particle->IsPlay())
		{
			particle->Play(Vector3());
		}


		if (myCollider->IsCollision(targetMonster->GetCollider()))
		{
			targetMonster->Hit(skillDamage);
			myCollider->SetActive(false);
			isRun = false;
			return;
		}
	}
}

void F_000_Basic_Atttack::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		particle->Render();
		myCollider->Render();
	}
}

void F_000_Basic_Atttack::UseSkill(MonsterBase* monsterbase)
{
	if (isRun || isCooldown || monsterbase == nullptr) return;

	if (FireMage_in* c = dynamic_cast<FireMage_in*>(owner))
	{
		c->SetState(FireMage_in::State::ATTACK1);
	}

	skillDamage = owner->GetStat().damage;
	targetMonster = monsterbase;
	animStart = 0;
	isRun = true;
	isCooldown = true;

	myCollider->Pos() = owner->GlobalPos();
	myCollider->Pos().y += owner->Scale().y;
	myCollider->SetActive(true);
	myCollider->UpdateWorld();
}