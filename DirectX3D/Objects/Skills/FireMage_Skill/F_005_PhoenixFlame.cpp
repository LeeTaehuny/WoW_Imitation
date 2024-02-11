#include "Framework.h"
#include "F_005_PhoenixFlame.h"

F_005_PhoenixFlame::F_005_PhoenixFlame() : ActiveSkill(SkillType::Target)
{
	// 날아갈 콜라이더
	myCollider = new SphereCollider();
	myCollider->SetActive(false);
	// 충돌 시 데미지 판정을 위한 콜라이더
	hitCollider = new SphereCollider(5.0f);
	hitCollider->SetActive(false);

	// 선행 스킬
	prevSkills.push_back("F_002_FireBlast");
	prevSkills.push_back("F_003_Pyrotechnics");

	// 스킬 속도
	speed = 20.0f;

	// 스킬 데미지
	skillDamage = 100.0f;

	// 쿨타임 설정 (25초)
	MAX_delay = 25.0f;
	coolTime = MAX_delay;

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	// 이펙트 추가
	hitParticleSystem = new ParticleSystem("TextData/Particles/Fire/fireHit.fx");

	startEdge = new Transform();
	endEdge = new Transform();

	trail = new Trail(L"Textures/Effect/fireTrail.png", startEdge, endEdge, 5, 10.0f);

	// 소모 마냐량
	requiredMp = 40;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/05_PhoenixFlame.png");
}

F_005_PhoenixFlame::~F_005_PhoenixFlame()
{
	SAFE_DEL(myCollider);
	SAFE_DEL(hitCollider);
	SAFE_DEL(hitParticleSystem);
	SAFE_DEL(startEdge);
	SAFE_DEL(endEdge);
	SAFE_DEL(trail);
	SAFE_DEL(icon);
}

void F_005_PhoenixFlame::Update()
{
	if (!impact)
	{
		if (isRun)
		{
			startEdge->Pos() = myCollider->GlobalPos() + myCollider->Forward();
			endEdge->Pos() = myCollider->GlobalPos() + myCollider->Back();
		}
		else
		{
			startEdge->Pos() = owner->GlobalPos();
			endEdge->Pos() = owner->GlobalPos();

		}

		startEdge->UpdateWorld();
		endEdge->UpdateWorld();
	}
	else
	{
		hitParticleSystem->Play(hitCollider->Pos());
		impact = false;
	}

	ActiveSkill::Update();
	trail->Update();
	hitParticleSystem->Update();
}

void F_005_PhoenixFlame::Render()
{
	ActiveSkill::Render();

	hitParticleSystem->Render();

	if (isRun)
		trail->Render();
}

void F_005_PhoenixFlame::UseSkill(Collider* targetCollider)
{
	if (targetCollider == nullptr) return;

	if (!isRun && !isCooldown)
	{
		target = targetCollider;

		myCollider->Pos() = owner->GlobalPos();
		myCollider->UpdateWorld();
		myCollider->SetActive(true);

		startEdge->Pos() = myCollider->GlobalPos() + myCollider->Forward() * 3.0f;
		endEdge->Pos() = myCollider->GlobalPos() + myCollider->Back() * 3.0f;
		startEdge->UpdateWorld();
		endEdge->UpdateWorld();

		isRun = true;
		isCooldown = true;
	}
}
