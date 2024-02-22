#include "Framework.h"
#include "A_010_Bladestorm.h"

A_010_Bladestorm::A_010_Bladestorm() : ActiveSkill(SkillType::NonTarget)
{
	skillName = "A_010_Bladestorm";

	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 충돌 판정을 위한 콜라이더
	hitCollider = new SphereCollider(4.0f);
	hitCollider->SetActive(false);
	hitCollider->SetParent(myCollider);

	sword = new ModelInstancing("sword_2");

	for (int i = 0; i < 4; i++)
	{
		Transform* transform = sword->Add();
		transform->SetParent(myCollider);
		transform->SetActive(false);
		swordTransforms.push_back(transform);
	}
	
	swordTransforms[0]->Pos() = Vector3(2.0f, myCollider->Pos().y, 2.0f);
	swordTransforms[0]->Rot() = Vector3(2.0f, myCollider->Pos().y, 2.0f);
	swordTransforms[1]->Pos() = Vector3(-2.0f, myCollider->Pos().y, 2.0f);
	swordTransforms[1]->Rot() = Vector3(-2.0f, myCollider->Pos().y, 2.0f);
	swordTransforms[2]->Pos() = Vector3(-2.0f, myCollider->Pos().y, -2.0f);
	swordTransforms[2]->Rot() = Vector3(-2.0f, myCollider->Pos().y, -2.0f);
	swordTransforms[3]->Pos() = Vector3(2.0f, myCollider->Pos().y, -2.0f);
	swordTransforms[3]->Rot() = Vector3(2.0f, myCollider->Pos().y, -2.0f);
	
	sword->SetParent(myCollider);

	// 지속 시간 설정
	curTime = 0.0f;
	MAX_duration = 8.0f;

	// 쿨타임 설정 (1분 30초)
	MAX_delay = 90.0f;
	coolTime = MAX_delay;

	// 선행 스킬
	prevSkills.push_back("A_008_Massacre");

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	// 소모 마나량
	requiredMp = 100.0f;

	// 아이콘 추가
	icon = new Quad(L"Textures/Character_Skill_Icon/ArmsWarrior/10_Bladestorm.png");

	// 피격 리스트 초기화
	hitTime = 0.0f;
	MAX_hitTime = 0.5f;

	additiveDamage = 1.0f;

	usingType = UseType::NON_Data;
}

A_010_Bladestorm::~A_010_Bladestorm()
{
	SAFE_DEL(sword);
	SAFE_DEL(myCollider);
	SAFE_DEL(hitCollider);
}

void A_010_Bladestorm::Update()
{
	if (owner->GetWeapon() == nullptr) return;

	if (isRun)
	{
		myCollider->Rot().y += DELTA * 8.0f;

		// myCollider와의 충돌 체크
		vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
		vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
		vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();

		for (MonsterBase* monster : cols1)
		{
			if (find(hit.begin(), hit.end(), monster) == hit.end())
			{
				if (hitCollider->IsCollision(monster->GetCollider()))
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);
					hit.push_back(monster);
				}
			}
		}

		for (MonsterBase* monster : cols2)
		{
			if (find(hit.begin(), hit.end(), monster) == hit.end())
			{
				if (hitCollider->IsCollision(monster->GetCollider()))
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);
					hit.push_back(monster);
				}
			}
		}

		for (MonsterBase* monster : cols3)
		{
			if (find(hit.begin(), hit.end(), monster) == hit.end())
			{
				if (hitCollider->IsCollision(monster->GetCollider()))
				{
					// 충돌한 몬스터들에게 데미지 주기
					// * 매개변수로 owner의 공격력과 번호 저장하기
					monster->Hit(skillDamage);
					hit.push_back(monster);
				}
			}
		}

		// 지속시간 업데이트
		curTime += DELTA;

		if (curTime >= MAX_duration)
		{
			curTime = 0.0f;
			isRun = false;
			hit.clear();
		}

		// 1초마다 공격 리스트 초기화
		hitTime += DELTA;

		if (hitTime >= MAX_hitTime)
		{
			hitTime = 0.0f;
			hit.clear();
		}

		FOR(4) swordTransforms[i]->UpdateWorld();
		sword->Update();
		myCollider->UpdateWorld();
		hitCollider->UpdateWorld();
	}
	else
	{
		hitTime = 0.0f;
		myCollider->SetActive(false);
		hitCollider->SetActive(false);
	}

	if (isCooldown)
	{
		Cooldown();
	}
}

void A_010_Bladestorm::Render()
{
	if (isRun)
	{
		myCollider->Render();
		hitCollider->Render();
		sword->Render();
	}
}

void A_010_Bladestorm::UseSkill()
{
	if (!isRun && !isCooldown)
	{
		isCooldown = true;
		isRun = true;

		myCollider->SetActive(true);
		hitCollider->SetActive(true);
		
		myCollider->UpdateWorld();
		hitCollider->UpdateWorld();

		FOR(4) swordTransforms[i]->SetActive(true);

		owner->GetStat().mp -= requiredMp;

		if (owner->GetStat().mp < 0)
		{
			owner->GetStat().mp = 0;
		}

		Init();
	}
}

void A_010_Bladestorm::Init()
{
	myCollider->SetParent(owner->GetCollider());

	// 스킬 데미지
	int temp = owner->GetStat().damage;
	skillDamage = temp * additiveDamage;
}
