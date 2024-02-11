#include "Framework.h"
#include "F_001_Pyroblast.h"

F_001_Pyroblast::F_001_Pyroblast() : ActiveSkill(SkillType::Target)
{
	// 날아갈 콜라이더
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 충돌 시 데미지 판정을 위한 콜라이더
	hitCollider = new SphereCollider();
	hitCollider->SetActive(false);

	// 스킬 속도
	speed = 20.0f;

	// 스킬 데미지
	skillDamage = 100.0f;

	// 쿨타임 설정 (4초)
	MAX_delay = 4.0f;
	coolTime = MAX_delay;

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	// 이펙트 추가
	hitParticleSystem = new ParticleSystem("TextData/Particles/Fire/fireHit.fx");
	fireBallParticle = new ParticleSystem("TextData/Particles/Fire/fireBall.fx");

	// 소모 마냐량
	requiredMp = 20;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/01_Pyroblast.png");
}

F_001_Pyroblast::~F_001_Pyroblast()
{
	SAFE_DEL(myCollider);
	SAFE_DEL(hitCollider);
	SAFE_DEL(hitParticleSystem);
	SAFE_DEL(fireBallParticle);
	SAFE_DEL(icon);
}

void F_001_Pyroblast::Update()
{
	if (!impact)
	{
		if (isRun)
		{
			if (!fireBallParticle->IsPlay())
				fireBallParticle->Play(myCollider->Pos());
			else
				fireBallParticle->SetPos(myCollider->Pos());
		}
	}
	else
	{
		hitParticleSystem->Play(hitCollider->Pos());
		fireBallParticle->Stop();
		impact = false;
	}


	ActiveSkill::Update();
	fireBallParticle->Update();
	hitParticleSystem->Update();
}

void F_001_Pyroblast::Render()
{
	ActiveSkill::Render();

	hitParticleSystem->Render();

	if (isRun)
		fireBallParticle->Render();
}

void F_001_Pyroblast::UseSkill(Collider* targetCollider)
{
	if (targetCollider == nullptr) return;

	if (!isRun && !isCooldown)
	{
		target = targetCollider;

		myCollider->Pos() = owner->GlobalPos();
		myCollider->UpdateWorld();
		myCollider->SetActive(true);

		isRun = true;
		isCooldown = true;
	}
}
