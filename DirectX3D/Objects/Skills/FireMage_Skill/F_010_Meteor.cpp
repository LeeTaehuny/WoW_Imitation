#include "Framework.h"
#include "F_010_Meteor.h"

F_010_Meteor::F_010_Meteor() : ActiveSkill(SkillType::Target)
{
	skillName = "F_010_Meteor";

	// 날아갈 콜라이더
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 구체
	meteorSphere = new Sphere(0.5f);
	meteorSphere->SetParent(myCollider);
	meteorSphere->GetMaterial()->SetDiffuseMap(L"Textures/Effect/meteorBase.png");

	// 충돌 시 데미지 판정을 위한 콜라이더
	hitCollider = new SphereCollider(5.0f);
	hitCollider->SetActive(false);

	// 스킬 속도
	speed = 10.0f;

	// 쿨타임 설정 (45초)
	MAX_delay = 4.0f;
	coolTime = MAX_delay;

	// 선행 스킬
	prevSkills.push_back("F_008_FlameOn");

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	// 이펙트 추가
	hitParticleSystem = new ParticleSystem("TextData/Particles/Fire/meteorHit.fx");
	fireBallParticle = new ParticleSystem("TextData/Particles/Fire/fireBall.fx");

	// 소모 마냐량
	requiredMp = 100;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/10_Meteor.png");

	// 스킬 지연 발사
	delayTime = 0.0f;
	MAX_delayAnim = 1.0f;

	additiveDamage = 1.0f;

	usingType = UseType::monster_Data;
}

F_010_Meteor::~F_010_Meteor()
{
	SAFE_DEL(myCollider);
	SAFE_DEL(hitCollider);
	SAFE_DEL(hitParticleSystem);
	SAFE_DEL(fireBallParticle);
	SAFE_DEL(meteorSphere);
	SAFE_DEL(icon);
}

void F_010_Meteor::Update()
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
				if (!fireBallParticle->IsPlay())
					fireBallParticle->Play(myCollider->Pos());
				else
					fireBallParticle->SetPos(myCollider->Pos());
			}
		}
		else
		{
			hitParticleSystem->Play(hitCollider->Pos());
			fireBallParticle->Stop();
			impact = false;
		}


		ActiveSkill::Update();
		fireBallParticle->Update();
		hitParticleSystem->Update();
		meteorSphere->UpdateWorld();
	}
}

void F_010_Meteor::Render()
{
	ActiveSkill::Render();

	hitParticleSystem->Render();

	if (isRun)
	{
		meteorSphere->Render();
		fireBallParticle->Render();
	}
		
}

void F_010_Meteor::UseSkill(MonsterBase* monsterbase)
{
	if (owner->GetWeapon() == nullptr) return;

	if (monsterbase == nullptr) return;

	if (FireMage_in* player = dynamic_cast<FireMage_in*>(owner))
	{
		if (!isRun && !isCooldown)
		{
			if (player->GetState() == player->State::ATTACK1) return;

			target = monsterbase->GetCollider();

			myCollider->Pos() = { owner->GlobalPos().x, owner->GlobalPos().y + 10.0f, owner->GlobalPos().z };
			myCollider->UpdateWorld();
			myCollider->SetActive(true);

			meteorSphere->SetActive(true);
			meteorSphere->UpdateWorld();

			player->SetState(player->State::ATTACK1);
			owner->GetInstancing()->PlayClip(owner->GetIndex(), 4, 1.0f);

			isRun = true;
			isCooldown = true;

			delayTime = 0.0f;

			Init();
		}
	}
}

void F_010_Meteor::Init()
{
	// 스킬 데미지 설정
	int temp = owner->GetStat().damage;

	if (FireMage_in* mage = dynamic_cast<FireMage_in*>(owner))
	{
		if (mage->GetDoubleDamage())
		{
			skillDamage = 2 * temp * 3.0f * additiveDamage;
		}
		else
		{
			skillDamage = temp * 3.0f * additiveDamage;
		}
	}
}
