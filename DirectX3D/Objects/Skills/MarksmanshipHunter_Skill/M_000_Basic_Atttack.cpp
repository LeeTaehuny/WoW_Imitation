#include "Framework.h"
#include "M_000_Basic_Atttack.h"

M_000_Basic_Atttack::M_000_Basic_Atttack() : ActiveSkill(SkillType::Target)
{
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 30.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 기본 공격 딜레이
		MAX_delay = 0.3f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// 마나 소모 : 0%
		usingType = monster_Data;
	}
}

M_000_Basic_Atttack::~M_000_Basic_Atttack()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete particle;
}

void M_000_Basic_Atttack::Update()
{
	if (isCooldown)
		ActiveSkill::Cooldown();

	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		direction = (targetMonster->GetCollider()->GlobalPos() - myCollider->GlobalPos()).GetNormalized();
		myCollider->Pos() += direction * speed * DELTA;
		myCollider->UpdateWorld();

		arrow->Rot().y = atan2(direction.x, direction.z) - 1.6f;;
		arrow->SetActive(true);
		arrow->UpdateWorld();

		if (myCollider->IsCollision(targetMonster->GetCollider()))
		{
			targetMonster->Hit(skillDamage);
			myCollider->SetActive(false);
			arrow->SetActive(false);
			arrow->SetIsRun(false);
			isRun = false;
			return;
		}
	}
}

void M_000_Basic_Atttack::Render()
{
	//myCollider->Render();
}

void M_000_Basic_Atttack::UseSkill(MonsterBase* monsterbase)
{
	if (isRun || isCooldown || monsterbase == nullptr) return;

	if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(owner))
	{
		c->SetState(MarksmanshipHunter_in::State::ATTACK1);
	}

	skillDamage = owner->GetStat().damage;
	targetMonster = monsterbase;
	animStart = 0;
	isRun = true;
	isCooldown = true;

	myCollider->Pos() = owner->GlobalPos();
	myCollider->Pos().y += owner->Scale().y;
	myCollider->SetActive(true);
	myCollider->UpdateWorld();

	arrow = ARROW->GetActiveArrow();
	arrow->SetParent(myCollider);
	arrow->UpdateWorld();
}