#include "Framework.h"
#include "H_008_Divine_Hymn.h"

H_008_Divine_Hymn::H_008_Divine_Hymn() : ActiveSkill(SkillType::NonTarget)
{
	skillName = "H_008_Divine_Hymn";

	hitCollider = new SphereCollider();
	hitCollider->SetActive(false);
	hitCollider->Scale().x += 5;
	hitCollider->Scale().z += 5;

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본 쿨타임은 : (60초)
		MAX_delay = 3.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 : 2.5%
		usingType = NON_Data;
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/008.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "H_005_Censure";
	prevSkills[1] = "H_007_Cosmic_Ripple";
	particle1 = new ParticleSystem("TextData/Particles/Priests/Skill08.fx");
	particle2 = new ParticleSystem("TextData/Particles/Priests/Skill08.fx");
}

H_008_Divine_Hymn::~H_008_Divine_Hymn()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete particle1;
	delete particle2;
}

void H_008_Divine_Hymn::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		if (!particle1->IsPlay())
		{
			particle1->Play(owner->Pos());
		}
		else
		{
			particle1->SetPos(owner->Pos());
			particle1->Update();
		}

		startTimeDelay += DELTA;
		if (startTimeDelay >= 0.75)
		{
			if (!particle2->IsPlay())
			{
				particle2->Play(owner->Pos());
			}
			else
			{
				particle2->SetPos(owner->Pos());
				particle2->Update();
			}
		}

		hitCollider->Pos() = owner->Pos();
		hitCollider->UpdateWorld();

		for (CH_Base_ver2* ch : CH->GetCharcterData())
		{
			if (ch == owner) continue;

			if (hitCollider->IsCollision(ch->GetCollider()))
			{
				ch->GetStat().hp += skillDamage * DELTA;
				if (owner->GetStat().hp >= owner->GetStat().maxHp)
				{
					owner->GetStat().hp = owner->GetStat().maxHp;
				}
			}
		}

		tickTime -= DELTA;
		if (tickTime <= 0)
		{
			tickTime = Max_tickTime;
			owner->GetStat().mp -= 50;

			if (owner->GetStat().mp <= 0)
			{
				isRun = false;
				isCooldown = true;
			}
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void H_008_Divine_Hymn::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		particle1->Render();
		particle2->Render();
	}
}

void H_008_Divine_Hymn::UseSkill()
{
	if (isCooldown) return;

	if (!isRun)
	{
		if (HolyPriest_in* c = dynamic_cast<HolyPriest_in*>(owner))
		{
			c->SetState(HolyPriest_in::State::ATTACK1);
		}

		animStart = 0;
		isRun = true;
		hitCollider->SetActive(true);
	}
	else if (isRun)
	{
		isRun = false;
		hitCollider->SetActive(false);
		isCooldown = true;
	}

	//startTimeDelay = 0;
	skillDamage = owner->GetStat().damage * 0.1f;
}