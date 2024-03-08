#include "Framework.h"
#include "H_003_Guardian_Spirit.h"

#include "Objects/UI/PlayerUI_Bar.h"
#include "Objects/UI/PartyUI_Bar.h"

H_003_Guardian_Spirit::H_003_Guardian_Spirit() : ActiveSkill(SkillType::Target)
{
	skillName = "H_003_Guardian_Spirit";

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본은 (180초)
		MAX_delay = 10.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 : 0.9%
		requiredMp = 9;
		usingType = character_Data;
	}

	// 작동하고 있는 시간 (기본은 10초)
	Max_runTime = 10;
	runTime = Max_runTime;

	Max_healingTick = Max_runTime * 0.1f;

	spirit = new Quad(L"Textures/Effect/Emerald_Snow.png");
	spirit->Scale() *= 0.05f;
	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/003.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "H_001_Holy_Word_Serenity";
}

H_003_Guardian_Spirit::~H_003_Guardian_Spirit()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete spirit;

	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void H_003_Guardian_Spirit::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		if (!isOne_sound)
		{
			switch (owner->GetcreatureType())
			{
			case CreatureType::Player:
				Audio::Get()->Play("HP_03_using", owner->Pos(), 1.0f);
				break;
			}
			isOne_sound = true;
		}

		runTime -= DELTA;
		if (runTime <= 0)
		{
			runTime = Max_runTime;
			isRun = false;
		}

		healingTick -= DELTA;
		if (healingTick <= 0)
		{
			healingTick = Max_healingTick;

			healingTarget->GetStat().hp += skillDamage;
			if (healingTarget->GetStat().hp >= healingTarget->GetStat().maxHp)
			{
				healingTarget->GetStat().hp = healingTarget->GetStat().maxHp;
			}

			if (healingTarget->GetcreatureType() == CreatureType::Player)
				healingTarget->GetPlayerUI()->SetHpPercent(healingTarget->GetStat().hp / healingTarget->GetStat().maxHp);
			else
				CH->GetPartyUI()->SetHpPercent(healingTarget->GetStat().hp / healingTarget->GetStat().maxHp, stoi(healingTarget->GetTag().c_str()));
		}

		// 스탯이 추가되면 이곳에 추가 효과를 주면 됩니다.
		Vector3 lll = healingTarget->GlobalPos();
		lll.y += healingTarget->GlobalScale().y * 4.5f;
		spirit->Pos() = lll;
		spirit->Rot() = CAM->Rot();
		spirit->UpdateWorld();
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void H_003_Guardian_Spirit::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		blendState[1]->SetState();
		depthState[1]->SetState();

		spirit->Render();

		blendState[0]->SetState();
		depthState[0]->SetState();
	}
}

void H_003_Guardian_Spirit::UseSkill(CH_Base_ver2* chbase)
{
	if (isRun || isCooldown || chbase == nullptr ||
		owner->GetStat().mp < requiredMp ||
		!owner->GetWeapon()) return;

	skillDamage = owner->GetStat().damage * 0.2f;
	owner->GetStat().mp -= requiredMp;

	if (HolyPriest_in* c = dynamic_cast<HolyPriest_in*>(owner))
	{
		c->SetState(HolyPriest_in::State::ATTACK1);
	}

	animStart = 0;
	healingTarget = chbase;
	runTime = Max_runTime;
	isRun = true;
	isCooldown = true;
	isOne_sound = false;
}