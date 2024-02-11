#include "Framework.h"

P_004_HOTR::P_004_HOTR() : ActiveSkill(SkillType::Target)
{
	/*
	스킬의 효과

	적 한 명을 공격하고 그 적으로부터 파동의 형태로 주변의 적들에게도 피해를 준다
	*/

	myCollider = new SphereCollider(2.5f);
	myCollider->SetActive(false);
	hitCollider = new SphereCollider();
	hitCollider->SetActive(false);

	root = new Transform();
	myCollider->SetParent(root);

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 100.0f;

		// 쿨타임 설정 (5초)
		MAX_delay = 5.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 : 0.32%
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/004.jpg");
	holy_wave = new Quad(L"Textures/Effect/alpha_gold_snow.png");
	holy_wave->Rot().x = 1.7f;
	holy_wave->Scale() *= 0.05f;
	holy_wave->SetParent(hitCollider);

	FOR(2) blendState[i] = new BlendState();
	blendState[1]->Alpha(true); //알파 적용 (반투명 설정 있으면 적용)

	// 선행 스킬의 이름은 번호로 지정 
	// 001 : 응징의 방패를 선행 스킬로 필요로 한다는 의미
	prevSkills.resize(1);
	prevSkills[0] = "P_001_Avengers_Shield";
}

P_004_HOTR::~P_004_HOTR()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete root;
	delete holy_wave;

	FOR(2) delete blendState[i];
}

void P_004_HOTR::Update()
{
	// 무기를 든 손으로 콜라이더를 지정
	if (hitCollider->Active())
	{
		// 그냥 포스로 하면 한쪽 축으로만 값이 커져서 3개 축에 직접 더함
		float ful = 10.5f; // 값 변경을 쉽게 하기 위한 변수
		hitCollider->Scale().x += ful * DELTA;
		//hitCollider->Scale().y += ful * DELTA;
		hitCollider->Scale().z += ful * DELTA;
	
		vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
		for (MonsterBase* monster : cols1)
		{
			if (hitCollider->IsCollision(monster->GetCollider()))
			{
				// 충돌한 몬스터들에게 데미지 주기
				// * 매개변수로 owner의 공격력과 번호 저장하기
				monster->Hit(skillDamage);
			}
		}
		cols1 = MONSTER->GetSkeleton();
		for (MonsterBase* monster : cols1)
		{
			if (hitCollider->IsCollision(monster->GetCollider()))
			{
				// 충돌한 몬스터들에게 데미지 주기
				// * 매개변수로 owner의 공격력과 번호 저장하기
				monster->Hit(skillDamage);
			}
		}
		cols1 = MONSTER->GetSkeleton_Knight();
		for (MonsterBase* monster : cols1)
		{
			if (hitCollider->IsCollision(monster->GetCollider()))
			{
				// 충돌한 몬스터들에게 데미지 주기
				// * 매개변수로 owner의 공격력과 번호 저장하기
				monster->Hit(skillDamage);
			}
		}
		
		// 히트 범위가 일정 수준을 넘어가면 액티브를 끄면서 동작 정지
		if (hitCollider->Scale().x >= 7)
		{
			hitCollider->SetActive(false);
		}
	}
	else
	{
		hitCollider->Scale() = Vector3(1, 1, 1);
		hitCollider->Pos() = Vector3(0, -50, 0);
		myCollider->SetActive(false);
	}

	root->SetWorld(owner->GetInstancing()->GetTransformByNode(owner->GetIndex(), 38));
	myCollider->UpdateWorld();
	hitCollider->UpdateWorld();
	holy_wave->UpdateWorld();

	ActiveSkill::Cooldown();
}

void P_004_HOTR::Render()
{
	//myCollider->Render();
	//hitCollider->Render();

	blendState[1]->SetState();
	if (hitCollider->Active())
		holy_wave->Render();
	blendState[0]->SetState();
}

void P_004_HOTR::UseSkill(Collider* targetCollider)
{
	if (!isCooldown && targetCollider == nullptr) return;
	target = targetCollider;

	myCollider->SetActive(true);
	//myCollider->Pos() = owner->GlobalPos();

	// 지금은 스킬 사용 직후 판정하는 것으로 하지만
	// 나중에는 공격 모션이 끝나면 정보를 받는 것으로 변경 해야 함
	if (target->IsCollision(myCollider))
	{
		hitCollider->SetActive(true);
		hitCollider->Pos() = target->GlobalPos();
		hitCollider->Pos().y = target->GlobalScale().y * 0.5f;
		hitCollider->UpdateWorld();
		isRun = true;
		isCooldown = true;
	}
}