#include "Framework.h"
#include "F_005_PhoenixFlame.h"

F_005_PhoenixFlame::F_005_PhoenixFlame() : ActiveSkill(SkillType::Target)
{
	skillName = "F_005_PhoenixFlame";

	// 날아갈 콜라이더
	myCollider = new SphereCollider();
	myCollider->SetActive(false);
	// 충돌 시 데미지 판정을 위한 콜라이더
	hitCollider = new SphereCollider(5.0f);
	hitCollider->SetActive(false);

	// 선행 스킬
	prevSkills.push_back("F_002_FireBlast");
	prevSkills.push_back("F_003_Pyrotechnics");

	// 스킬 속도
	speed = 20.0f;

	// 쿨타임 설정 (25초)
	MAX_delay = 25.0f;
	coolTime = MAX_delay;

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	// 이펙트 추가
	hitParticleSystem = new ParticleSystem("TextData/Particles/Fire/fireHit.fx");

	startEdge = new Transform();
	endEdge = new Transform();

	trail = new Trail(L"Textures/Effect/fireTrail.png", startEdge, endEdge, 5, 10.0f);

	// 소모 마냐량
	requiredMp = 40;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/05_PhoenixFlame.png");

	// 스킬 지연 발사
	delayTime = 0.0f;
	MAX_delayAnim = 2.0f;

	additiveDamage = 1.0f;

	usingType = UseType::monster_Data;

	// 스킬 사운드
	Audio::Get()->Add("F_005", "Sounds/FireMage/F_005.ogg", false, false, true);
}

F_005_PhoenixFlame::~F_005_PhoenixFlame()
{
	SAFE_DEL(myCollider);
	SAFE_DEL(hitCollider);
	SAFE_DEL(hitParticleSystem);
	SAFE_DEL(startEdge);
	SAFE_DEL(endEdge);
	SAFE_DEL(trail);
	SAFE_DEL(icon);
}

void F_005_PhoenixFlame::Update()
{
	if (owner->GetWeapon() == nullptr) return;

	if (delayTime < MAX_delayAnim && isRun)
	{
		delayTime += DELTA;

		if (delayTime >= MAX_delayAnim)
		{
			if (owner->GetcreatureType() == CreatureType::Player)
			{
				Audio::Get()->Play("F_005", owner->Pos(), 1.0f);
			}
		}
	}
	else
	{
		if (!impact)
		{
			if (isRun)
			{
				startEdge->Pos() = myCollider->GlobalPos() + myCollider->Forward();
				endEdge->Pos() = myCollider->GlobalPos() + myCollider->Back();
			}
			else
			{
				startEdge->Pos() = owner->GlobalPos();
				endEdge->Pos() = owner->GlobalPos();

			}

			startEdge->UpdateWorld();
			endEdge->UpdateWorld();
		}
		else
		{
			hitParticleSystem->Play(hitCollider->Pos());
			impact = false;
		}

		ActiveSkill::Update();
		trail->Update();
		hitParticleSystem->Update();
	}
}

void F_005_PhoenixFlame::Render()
{
	ActiveSkill::Render();

	hitParticleSystem->Render();

	if (isRun)
		trail->Render();
}

void F_005_PhoenixFlame::UseSkill(MonsterBase* monsterbase)
{
	if (owner->GetWeapon() == nullptr) return;

	if (monsterbase == nullptr) return;

	if (FireMage_in* player = dynamic_cast<FireMage_in*>(owner))
	{
		if (!isRun && !isCooldown)
		{
			if (player->GetState() == player->State::ATTACK1) return;

			target = monsterbase->GetCollider();

			myCollider->Pos() = owner->GlobalPos();
			myCollider->UpdateWorld();
			myCollider->SetActive(true);

			startEdge->Pos() = myCollider->GlobalPos() + myCollider->Forward() * 3.0f;
			endEdge->Pos() = myCollider->GlobalPos() + myCollider->Back() * 3.0f;
			startEdge->UpdateWorld();
			endEdge->UpdateWorld();

			player->SetState(player->State::ATTACK1);
			owner->GetInstancing()->PlayClip(owner->GetIndex(), 3, 1.0f);

			isRun = true;
			isCooldown = true;

			delayTime = 0.0f;

			owner->GetStat().mp -= requiredMp;

			if (owner->GetStat().mp < 0)
			{
				owner->GetStat().mp = 0;
			}

			Init();
		}
	}

	
}

void F_005_PhoenixFlame::Init()
{
	// 스킬 데미지 설정
	int temp = owner->GetStat().damage;

	if (FireMage_in* mage = dynamic_cast<FireMage_in*>(owner))
	{
		if (mage->GetDoubleDamage())
		{
			skillDamage = 2 * temp * 2.0f * additiveDamage;
		}
		else
		{
			skillDamage = temp * 2.0f * additiveDamage;
		}
	}
}
