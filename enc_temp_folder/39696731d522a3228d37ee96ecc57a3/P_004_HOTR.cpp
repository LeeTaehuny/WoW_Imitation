#include "Framework.h"

P_004_HOTR::P_004_HOTR() : ActiveSkill(SkillType::Target)
{
	myCollider = new SphereCollider(2.5f);
	myCollider->SetActive(false);
	hitCollider = new SphereCollider();
	hitCollider->SetActive(true);

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
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/004.jpg");
}

P_004_HOTR::~P_004_HOTR()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete root;
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

		if (hitCollider->Scale().x >= 7)
		{
			hitCollider->SetActive(false);
		}
	}
	else
	{
		//hitCollider->Scale() = Vector3(0.01f, 0.01f, 0.01f);
	}

	root->SetWorld(owner->GetInstancing()->GetTransformByNode(owner->GetIndex(), 38));
	
	//myCollider->GlobalPos() = root->Pos();
	myCollider->UpdateWorld();
	hitCollider->UpdateWorld();
}

void P_004_HOTR::Render()
{
	myCollider->Render();
	hitCollider->Render();
}

void P_004_HOTR::UseSkill(Collider* targetCollider)
{
	if (targetCollider == nullptr) return;
	target = targetCollider;

	myCollider->SetActive(true);
	//myCollider->Pos() = owner->GlobalPos();

	// 지금은 스킬 사용 직후 판정하는 것으로 하지만
	// 나중에는 공격 모션이 끝나면 정보를 받는 것으로 변경 해야 함
	if (target->IsCollision(myCollider))
	{
		hitCollider->SetActive(true);
		hitCollider->Pos() = target->Pos();
		isRun = true;
		isCooldown = true;
	}
}
