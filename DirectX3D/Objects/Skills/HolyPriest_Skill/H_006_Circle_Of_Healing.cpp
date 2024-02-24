#include "Framework.h"
#include "H_006_Circle_Of_Healing.h"

H_006_Circle_Of_Healing::H_006_Circle_Of_Healing() : ActiveSkill(SkillType::Target)
{
	skillName = "H_006_Circle_Of_Healing";

	hitCollider = new SphereCollider();
	hitCollider->SetActive(false);
	hitCollider->Scale().x *= 5;
	hitCollider->Scale().z *= 5;

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본은 (15초)
		MAX_delay = 5.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 : 3.3%
		requiredMp = 33;
		usingType = character_Data;
	}

	magic_circle = new Quad(L"Textures/Effect/Emerald_Snow.png");
	magic_circle->SetParent(hitCollider);
	magic_circle->Scale() *= 0.1f;
	magic_circle->Rot().x = 1.7f;
	FOR(2) blendState[i] = new BlendState();
	blendState[1]->Alpha(true);

	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/006.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "H_002_Holy_Word_Sanctify";

	healingTargets.resize(5);
	FOR(healingTargets.size())
	{
		particles.push_back(new ParticleSystem("TextData/Particles/Priests/Skill02.fx"));
	}
	FOR(healingTargets.size())
	{
		isOne.push_back(0);
	}
}

H_006_Circle_Of_Healing::~H_006_Circle_Of_Healing()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete magic_circle;

	FOR(2) delete blendState[i];
	for (ParticleSystem* particle : particles)
		delete particle;
}

void H_006_Circle_Of_Healing::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		hitCollider->Pos() = healingTargets[0]->GlobalPos();
		hitCollider->UpdateWorld();

		magic_circle->Rot().y += 2 * DELTA;
		magic_circle->UpdateWorld();

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

			if (particles[i]->IsPlay())
			{
				particles[i]->SetPos(healingTargets[i]->Pos());
				particles[i]->Update();
			}
			else
			{
				if (isOne[i] >= 1)
				{
					// 이 부분이 2번째 작동하는 것이라면
					// 일단 이 함수 자체를 종료하고 isRun도 거짓으로 변경
					isRun = false;
					isOne[i] = 0;

					healingTargets[i]->GetStat().hp += skillDamage;
					if (owner->GetStat().hp >= owner->GetStat().maxHp)
					{
						owner->GetStat().hp = owner->GetStat().maxHp;
					}

					healingTargets[i] = nullptr;
					continue;
				}
				isOne[i]++;
				particles[i]->Play(Vector3());
			}
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void H_006_Circle_Of_Healing::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		blendState[1]->SetState();
		magic_circle->Render();
		blendState[0]->SetState();

		FOR(particles.size())
		{
			if (particles[i]->IsPlay())
			{
				particles[i]->Render();
			}
		}
	}
}

void H_006_Circle_Of_Healing::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown || chbase == nullptr ||
		owner->GetStat().mp < requiredMp ||
		!owner->GetWeapon()) return;

	skillDamage = owner->GetStat().damage * 0.99f;
	owner->GetStat().mp -= requiredMp;

	if (HolyPriest_in* c = dynamic_cast<HolyPriest_in*>(owner))
	{
		c->SetState(HolyPriest_in::State::ATTACK1);
	}

	animStart = 0;
	hitCollider->SetActive(true);
	healingTargets[0] = chbase;
	isRun = true;
	isCooldown = true;
}