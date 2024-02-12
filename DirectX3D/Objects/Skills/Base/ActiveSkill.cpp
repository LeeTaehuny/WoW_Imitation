#include "Framework.h"
#include "ActiveSkill.h"

ActiveSkill::ActiveSkill(SkillType type)
	: SkillBase(SkillBaseType::Active), skillType(type)
{
	// 멤버 변수 초기화
	coolTime = MAX_delay;

	isCooldown = false;
	isRun = false;
	impact = false;
}

ActiveSkill::~ActiveSkill()
{
}

void ActiveSkill::Update()
{
	// 스킬이 실행 중이라면?
	if (isRun)
	{
		// 스킬 업데이트
		switch (skillType)
		{
		case SkillType::Target:
			TargetUpdate();
			break;
		case SkillType::NonTarget:
			NonTargetUpdate();
			break;
		}

		myCollider->UpdateWorld();
	}
	
	// 스킬이 쿨타임을 기다리는 상황이라면
	if (isCooldown)
	{
		Cooldown();
	}
}

void ActiveSkill::Render()
{
	myCollider->Render();
	hitCollider->Render();
}

void ActiveSkill::TargetUpdate()
{
	if (!target) return;

	// 방향 정보 갱신
	direction = (target->GlobalPos() - myCollider->GlobalPos()).GetNormalized();

	// 갱신된 방향으로 스킬 위치 업데이트
	myCollider->Pos() += direction * speed * DELTA;

	// 방향에 맞게 회전값 수정
	myCollider->Rot().y = atan2(direction.x, direction.z) + XM_PI;

	if (myCollider->IsCollision(target))
	{
		myCollider->SetActive(false);
		isRun = false;
		impact = true;
		hitCollider->Pos() = myCollider->Pos();
		hitCollider->SetActive(true);
		hitCollider->UpdateWorld();
	}

	if (hitCollider->Active())
	{
		// HitCollder와의 충돌 체크
		vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
		vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
		vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();

		for (MonsterBase* monster : cols1)
		{
			if (hitCollider->IsCollision(monster->GetCollider()))
			{
				// 충돌한 몬스터들에게 데미지 주기
				// * 매개변수로 owner의 공격력과 번호 저장하기
				monster->Hit(skillDamage);
			}
		}

		for (MonsterBase* monster : cols2)
		{
			if (hitCollider->IsCollision(monster->GetCollider()))
			{
				// 충돌한 몬스터들에게 데미지 주기
				// * 매개변수로 owner의 공격력과 번호 저장하기
				monster->Hit(skillDamage);
			}
		}

		for (MonsterBase* monster : cols3)
		{
			if (hitCollider->IsCollision(monster->GetCollider()))
			{
				// 충돌한 몬스터들에게 데미지 주기
				// * 매개변수로 owner의 공격력과 번호 저장하기
				monster->Hit(skillDamage);
			}
		}

		hitCollider->SetActive(false);
	}
}

void ActiveSkill::NonTargetUpdate()
{
	hitCollider->SetActive(true);

	// HitCollder와의 충돌 체크
	vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
	vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
	vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();
	
	for (MonsterBase* monster : cols1)
	{
		if (hitCollider->IsCollision(monster->GetCollider()))
		{
			// 충돌한 몬스터들에게 데미지 주기
			// * 매개변수로 owner의 공격력과 번호 저장하기
			monster->Hit(skillDamage);
		}
	}

	for (MonsterBase* monster : cols2)
	{
		if (hitCollider->IsCollision(monster->GetCollider()))
		{
			// 충돌한 몬스터들에게 데미지 주기
			// * 매개변수로 owner의 공격력과 번호 저장하기
			monster->Hit(skillDamage);
		}
	}

	for (MonsterBase* monster : cols3)
	{
		if (hitCollider->IsCollision(monster->GetCollider()))
		{
			// 충돌한 몬스터들에게 데미지 주기
			// * 매개변수로 owner의 공격력과 번호 저장하기
			monster->Hit(skillDamage);
		}
	}

	// TODO : 보스 제작 후 보스의 콜라이더도 추가

	hitCollider->SetActive(false);
	
}


void ActiveSkill::Cooldown()
{
	coolTime -= DELTA;

	if (coolTime <= 0)
	{
		coolTime = MAX_delay;
		isCooldown = false;
	}
}
