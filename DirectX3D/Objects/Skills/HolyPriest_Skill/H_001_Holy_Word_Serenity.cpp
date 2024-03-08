#include "Framework.h"
#include "H_001_Holy_Word_Serenity.h"

#include "Objects/UI/PlayerUI_Bar.h"
#include "Objects/UI/PartyUI_Bar.h"

H_001_Holy_Word_Serenity::H_001_Holy_Word_Serenity() : ActiveSkill(SkillType::Target)
{
	skillName = "H_001_Holy_Word_Serenity";

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본 쿨타임은 : (60초)
		MAX_delay = 5.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 : 2.5%
		requiredMp = 25;
		usingType = character_Data;
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/001.jpg");
	particle = new ParticleSystem("TextData/Particles/Priests/Skill01.fx");
}

H_001_Holy_Word_Serenity::~H_001_Holy_Word_Serenity()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete particle;
	delete healingTarget;
}

void H_001_Holy_Word_Serenity::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		Vector3 im = healingTarget->GlobalPos();
		im.y = healingTarget->GlobalScale().y * 0.5f;

		if (isOne == 0)
		{
			particle->Play(im);
			isOne++;

			// 체력을 회복시키고
			healingTarget->GetStat().hp += skillDamage;
			// 체력이 오버를 했다면 조정
			if (healingTarget->GetStat().hp >= healingTarget->GetStat().maxHp)
			{
				healingTarget->GetStat().hp = healingTarget->GetStat().maxHp;
			}

			if (healingTarget->GetcreatureType()== CreatureType::Player)
				healingTarget->GetPlayerUI()->SetHpPercent(healingTarget->GetStat().hp / healingTarget->GetStat().maxHp);
			else
				CH->GetPartyUI()->SetHpPercent(healingTarget->GetStat().hp / healingTarget->GetStat().maxHp, stoi(healingTarget->GetTag().c_str()));

			switch (owner->GetcreatureType())
			{
			case CreatureType::Player:
				Audio::Get()->Play("HP_01_using", owner->Pos(), 1.0f);
				break;
			}
		}
	

		if (particle->IsPlay())
		{
			particle->SetPos(healingTarget->Pos());
			particle->Update();
		}
		else
		{
			isRun = false;
			isOne = 0;
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void H_001_Holy_Word_Serenity::Render()
{
	if (particle->IsPlay())
	{
		if (animStart <= Max_animStart) return;

		particle->Render();
	}
}

void H_001_Holy_Word_Serenity::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown || chbase == nullptr ||
		owner->GetStat().mp < requiredMp ||
		!owner->GetWeapon()) return;

	if (HolyPriest_in* c = dynamic_cast<HolyPriest_in*>(owner))
	{
		c->SetState(HolyPriest_in::State::ATTACK1);
	}

	skillDamage = owner->GetStat().damage * 0.86f;
	owner->GetStat().mp -= requiredMp;

	animStart = 0;
	healingTarget = chbase;
	isRun = true;
	isCooldown = true;
}