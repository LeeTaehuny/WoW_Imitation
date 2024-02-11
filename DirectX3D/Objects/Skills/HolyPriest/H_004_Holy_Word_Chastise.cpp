#include "Framework.h"
#include "H_004_Holy_Word_Chastise.h"

H_004_Holy_Word_Chastise::H_004_Holy_Word_Chastise() : ActiveSkill(SkillType::Target)
{
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

		// // 마나 소모 : 2.0%
	}

	particle = new ParticleSystem("TextData/Particles/Priests/Skill04.fx");

	icon = new Quad(L"Textures/Character_Skill_Icon/HolyPriest/004.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "H_001_Holy_Word_Serenity";
}

H_004_Holy_Word_Chastise::~H_004_Holy_Word_Chastise()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete particle;
	delete targetMonster;
}

void H_004_Holy_Word_Chastise::Update()
{
	if (isRun)
	{
		isRun = false;
		particle->Play(Vector3());

		// 몬스터에게 데미지를 주고 상태이상 상태를 주려면
		// 여기서 추가를 하시면 됩니다.

		// 불신임 특성이 찍혀 있다면 원래 행동불능 상태를 주는 것이
		// 기절로 바뀝니다.
	}
	if (particle->IsPlay())
	{
		Vector3 lll = targetMonster->GetCollider()->GlobalPos();
		lll.y += targetMonster->GetCollider()->GlobalScale().y * 2;

		particle->SetPos(lll);
		particle->Update();
	}

	ActiveSkill::Cooldown();
}

void H_004_Holy_Word_Chastise::Render()
{
	if (particle->IsPlay())
	{
		particle->Render();
	}
}

void H_004_Holy_Word_Chastise::UseSkill(MonsterBase* monsterbase)
{
	if (isCooldown || monsterbase == nullptr) return;

	targetMonster = monsterbase;
	isRun = true;
	isCooldown = true;
}
