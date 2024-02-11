#include "Framework.h"
#include "F_002_FireBlast.h"

F_002_FireBlast::F_002_FireBlast() : ActiveSkill(SkillType::Target)
{
	// 스킬 데미지
	skillDamage = 100.0f;

	// 쿨타임 설정 (5초)
	MAX_delay = 5.0f;
	coolTime = MAX_delay;

	// 선행 스킬
	prevSkills.push_back("F_001_Pyroblast");

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	// 이펙트 추가
	hitParticleSystem = new ParticleSystem("TextData/Particles/Fire/targetBasicFire.fx");

	// 소모 마냐량
	requiredMp = 10;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/FireMage/02_FireBlast.png");
}

F_002_FireBlast::~F_002_FireBlast()
{
	SAFE_DEL(hitParticleSystem);
	SAFE_DEL(icon);
}

void F_002_FireBlast::Update()
{
	hitParticleSystem->Update();

	if (isCooldown)
	{
		Cooldown();
	}

	if (isRun)
	{
		// 해당 충돌체의 주인 찾기
		vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
		vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
		vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();

		for (MonsterBase* monster : cols1)
		{
			if (monster->GetCollider() == target)
			{
				// 충돌한 몬스터들에게 데미지 주기
				// * 매개변수로 owner의 공격력과 번호 저장하기
				monster->Hit(skillDamage);

				hitParticleSystem->Play(target->GlobalPos());
				isRun = false;
				return;
			}
		}

		for (MonsterBase* monster : cols2)
		{
			if (monster->GetCollider() == target)
			{
				// 충돌한 몬스터들에게 데미지 주기
				// * 매개변수로 owner의 공격력과 번호 저장하기
				monster->Hit(skillDamage);

				hitParticleSystem->Play(target->GlobalPos());
				isRun = false;
				return;
			}
		}

		for (MonsterBase* monster : cols3)
		{
			if (monster->GetCollider() == target)
			{
				// 충돌한 몬스터들에게 데미지 주기
				// * 매개변수로 owner의 공격력과 번호 저장하기
				monster->Hit(skillDamage);

				hitParticleSystem->Play(target->GlobalPos());
				isRun = false;
				return;
			}
		}
	}
}

void F_002_FireBlast::Render()
{
	hitParticleSystem->Render();
}

void F_002_FireBlast::UseSkill(Collider* targetCollider)
{
	if (targetCollider == nullptr) return;

	if (!isRun && !isCooldown)
	{
		target = targetCollider;

		isRun = true;
		isCooldown = true;
	}
}
