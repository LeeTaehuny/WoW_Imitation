#include "Framework.h"
#include "F_010_Meteor.h"

F_010_Meteor::F_010_Meteor() : ActiveSkill(SkillType::Target)
{
	// 날아갈 콜라이더
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 구체
	meteorSphere = new Sphere(0.5f);
	meteorSphere->SetParent(myCollider);
	meteorSphere->GetMaterial()->SetDiffuseMap(L"Textures/Effect/meteorBase.png");

	// 충돌 시 데미지 판정을 위한 콜라이더
	hitCollider = new SphereCollider(5.0f);
	hitCollider->SetActive(false);

	// 스킬 속도
	speed = 10.0f;

	// 스킬 데미지
	skillDamage = 100.0f;

	// 쿨타임 설정 (45초)
	MAX_delay = 45.0f;
	coolTime = MAX_delay;

	// 선행 스킬
	prevSkills.push_back("F_008_FlameOn");

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	// 이펙트 추가
	hitParticleSystem = new ParticleSystem("TextData/Particles/Fire/meteorHit.fx");
	fireBallParticle = new ParticleSystem("TextData/Particles/Fire/fireBall.fx");

	// 소모 마냐량
	requiredMp = 100;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/10_Meteor.png");
}

F_010_Meteor::~F_010_Meteor()
{
	SAFE_DEL(myCollider);
	SAFE_DEL(hitCollider);
	SAFE_DEL(hitParticleSystem);
	SAFE_DEL(fireBallParticle);
	SAFE_DEL(meteorSphere);
	SAFE_DEL(icon);
}

void F_010_Meteor::Update()
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
	meteorSphere->UpdateWorld();
}

void F_010_Meteor::Render()
{
	ActiveSkill::Render();

	hitParticleSystem->Render();

	if (isRun)
	{
		meteorSphere->Render();
		fireBallParticle->Render();
	}
		
}

void F_010_Meteor::UseSkill(Collider* targetCollider)
{
	if (targetCollider == nullptr) return;

	if (!isRun && !isCooldown)
	{
		target = targetCollider;

		myCollider->Pos() = { owner->GlobalPos().x, owner->GlobalPos().y + 10.0f, owner->GlobalPos().z };
		myCollider->UpdateWorld();
		myCollider->SetActive(true);

		meteorSphere->SetActive(true);

		isRun = true;
		isCooldown = true;
	}
}
