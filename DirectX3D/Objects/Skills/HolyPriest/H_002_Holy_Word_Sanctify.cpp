#include "Framework.h"
#include "H_002_Holy_Word_Sanctify.h"

H_002_Holy_Word_Sanctify::H_002_Holy_Word_Sanctify() : ActiveSkill(SkillType::NonTarget)
{
	hitCollider = new SphereCollider();
	hitCollider->SetActive(true);
	hitCollider->Scale().x += 8;
	hitCollider->Scale().z += 8;
	hitCollider->UpdateWorld();

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

		// // 마나 소모 : 3.5%
		usingType = NON_Data;
	}

	// 지금은 5개의 파티클을 생성하지만 나중에 너무 무겁다고 판단이 된다면
	// 장판 계열로 이펙트를 바꿔야 할 듯
	FOR(5)
	{
		particles.push_back(new ParticleSystem("TextData/Particles/Priests/Skill02.fx"));
	}

	healingTargets.resize(5);
	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/002.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "H_001_Holy_Word_Serenity";
}

H_002_Holy_Word_Sanctify::~H_002_Holy_Word_Sanctify()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;

	for (ParticleSystem* particle : particles)
		delete particle;
}

void H_002_Holy_Word_Sanctify::Update()
{
	if (isRun)
	{
		isRun = false;

		int imsiValue = 0;
		for (CH_Base_ver2* ch : CH->GetCharcterData())
		{
			// 본인인의 정보를 받아왔다면 바로 다음 연산
			if (ch == owner) continue;

			// 히트 콜라이더에 충돌한 적을 직접 계산
			if (hitCollider->IsCollision(ch->GetCollider()))
			{
				// 체력이 낮은 순서대로 회복할거라면 나중에 추가 해야 할 필요가 있음
				// 우선 지금은 배열 순서대로 배정

				healingTargets[imsiValue] = ch;
				imsiValue++;
				if (imsiValue == 5) break;
				// 사이즈가 5가 되면 반복문 정지
			}
		}

		FOR(healingTargets.size())
		{
			if (healingTargets[i] == nullptr) continue;
			particles[i]->Play(healingTargets[i]->Pos());
		}

		hitCollider->SetActive(false);

		// 회복을 시킬거라면 이 반복문 전에 회복을 시켜야 함
		FOR(healingTargets.size())
			healingTargets[i] = nullptr;
	}

	FOR(particles.size())
	{
		if (particles[i]->IsPlay())
		{
			particles[i]->Update();
		}
	}

	ActiveSkill::Cooldown();
}

void H_002_Holy_Word_Sanctify::Render()
{
	//hitCollider->Render();

	FOR(particles.size())
	{
		if (particles[i]->IsPlay())
		{
			particles[i]->Render();
		}
	}
}

void H_002_Holy_Word_Sanctify::UseSkill()
{
	if (isCooldown) return;

	hitCollider->SetActive(true);
	hitCollider->Pos() = owner->GlobalPos();
	hitCollider->UpdateWorld();


	isRun = true;
	isCooldown = true;
}