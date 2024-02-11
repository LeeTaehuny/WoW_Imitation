#include "Framework.h"
#include "H_001_Holy_Word_Serenity.h"

H_001_Holy_Word_Serenity::H_001_Holy_Word_Serenity() : ActiveSkill(SkillType::Target)
{
	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본 쿨타임은 : (60초)
		MAX_delay = 60.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 : 2.5%
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
		isRun = false;

		Vector3 im = healingTarget->GlobalPos();
		im.y = healingTarget->GlobalScale().y * 0.5f;
		particle->Play(im);

		// 이 부분에서 해당 캐릭터의
		// 체력을 회복시키는 부분을 추가하면 될 것 같습니다.
	}

	if (particle->IsPlay())
	{
		particle->SetPos(healingTarget->Pos());
		particle->Update();
	}
	ActiveSkill::Cooldown();
}

void H_001_Holy_Word_Serenity::Render()
{
	if (particle->IsPlay())
	{
		particle->Render();
	}
}

void H_001_Holy_Word_Serenity::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown || chbase == nullptr) return;

	healingTarget = chbase;
	isRun = true;
	isCooldown = true;
}