#include "Framework.h"
#include "FireBall.h"

FireBall::FireBall() : ActiveSkill(SkillType::Target)
{
	// 날아갈 콜라이더
	myCollider = new SphereCollider();
	myCollider->SetActive(false);
	// 충돌 시 데미지 판정을 위한 콜라이더
	hitCollider = new SphereCollider();
	hitCollider->SetActive(false);

	// 스킬 속도
	speed = 10.0f;

	// 스킬 데미지
	skillDamage = 100.0f;

	// 쿨타임 설정 (5초)
	MAX_delay = 5.0f;
	coolTime = MAX_delay;

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;


	// * 선행스킬이 없으면 않넣어도 됨.
	//prevSkills.push_back("");

	// 이펙트 추가
	hitParticleSystem = new ParticleSystem("TextData/Particles/Fire/fireHit.fx");

	startEdge = new Transform();
	endEdge = new Transform();

	trail = new Trail(L"Textures/Effect/Trail.png", startEdge, endEdge, 10, 10.0f);
}
FireBall::~FireBall()
{
	delete myCollider;
	delete hitCollider;
}

void FireBall::Update()
{
	if (!impact)
	{
		if (isRun)
		{
			startEdge->Pos() = myCollider->GlobalPos() + myCollider->Left() * 10.0f;
			endEdge->Pos() = myCollider->GlobalPos() - myCollider->Right() * 10.0f;

			startEdge->UpdateWorld();
			endEdge->UpdateWorld();
			trail->Update();
		}
		
	}
	else
	{
		hitParticleSystem->Play(hitCollider->Pos());
		impact = false;
	}


	ActiveSkill::Update();

	hitParticleSystem->Update();

}
void FireBall::Render()
{
	ActiveSkill::Render();

	hitParticleSystem->Render();

	trail->Render();
}

void FireBall::UseSkill(Collider* targetCollider)
{
	if (targetCollider == nullptr) return;

	if (!isRun && !isCooldown)
	{
		target = targetCollider;

		myCollider->Pos() = owner->GlobalPos();
		myCollider->SetActive(true);
		
		isRun = true;
		isCooldown = true;
	}
}