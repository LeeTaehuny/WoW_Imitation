#include "Framework.h"
#include "A_007_ColossusSmash.h"
#include "Objects/Character_/ArmsWarrior_in.h"
#include "Objects/Item/Weapon.h"

A_007_ColossusSmash::A_007_ColossusSmash() : ActiveSkill(SkillType::Target)
{
	skillName = "A_007_ColossusSmash";

	// 선행 스킬
	prevSkills.push_back("A_006_FueledbyViolence");

	// 날아갈 콜라이더
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 충돌 시 데미지 판정을 위한 콜라이더
	hitCollider = new SphereCollider();
	hitCollider->SetActive(false);

	// 스킬 속도
	speed = 20.0f;

	// 쿨타임 설정 (45초)
	MAX_delay = 45.0f;
	coolTime = MAX_delay;

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	// 이펙트 추가
	hitParticleSystem = new ParticleSystem("TextData/Particles/Warrior/swordHit.fx");
	swordBallParticle = new ParticleSystem("TextData/Particles/Warrior/swordBall.fx");

	// 소모 마냐량
	requiredMp = 20;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/01_Pyroblast.png");

	// 스킬 지연 발사
	delayTime = 0.0f;
	MAX_delayAnim = 1.0f;

	additiveDamage = 1.0f;

	usingType = UseType::monster_Data;
}

A_007_ColossusSmash::~A_007_ColossusSmash()
{
	SAFE_DEL(myCollider);
	SAFE_DEL(hitCollider);
	SAFE_DEL(hitParticleSystem);
	SAFE_DEL(swordBallParticle);
	SAFE_DEL(icon);
}

void A_007_ColossusSmash::Update()
{
	if (owner->GetWeapon() == nullptr) return;

	if (delayTime < MAX_delayAnim && isRun)
	{
		delayTime += DELTA;
	}
	else
	{
		if (!impact)
		{
			if (isRun)
			{
				if (!swordBallParticle->IsPlay())
					swordBallParticle->Play(myCollider->Pos());
				else
					swordBallParticle->SetPos(myCollider->Pos());
			}
		}
		else
		{
			hitParticleSystem->Play(hitCollider->Pos());
			swordBallParticle->Stop();
			impact = false;
		}

		ActiveSkill::Update();

		swordBallParticle->Update();
		hitParticleSystem->Update();
	}
}

void A_007_ColossusSmash::Render()
{
	ActiveSkill::Render();

	hitParticleSystem->Render();

	if (isRun)
		swordBallParticle->Render();
}

void A_007_ColossusSmash::UseSkill(MonsterBase* monsterbase)
{
	if (owner->GetWeapon() == nullptr) return;

	if (monsterbase == nullptr) return;

	if (ArmsWarrior_in* player = dynamic_cast<ArmsWarrior_in*>(owner))
	{
		if (!isRun && !isCooldown)
		{
			if (player->GetState() == player->State::ATTACK1) return;

			target = monsterbase->GetCollider();

			myCollider->Pos() = owner->GetWeapon()->GlobalPos();
			myCollider->UpdateWorld();
			myCollider->SetActive(true);

			player->SetState(player->State::ATTACK1);
			owner->GetInstancing()->PlayClip(owner->GetIndex(), 2, 1.0f);

			isRun = true;
			isCooldown = true;

			delayTime = 0.0f;

			Init();
		}
	}

	
}

void A_007_ColossusSmash::Init()
{
	// 스킬 데미지
	int temp = owner->GetStat().damage;
	skillDamage = temp * 3.0f * additiveDamage;
}
