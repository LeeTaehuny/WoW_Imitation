#include "Framework.h"
#include "P_032_Eye_Of_Tyr.h"

P_032_Eye_Of_Tyr::P_032_Eye_Of_Tyr() : ActiveSkill(SkillType::NonTarget)
{
	/*
	스킬의 효과

	방패에서 빛을 발산하여 범위내의 모든 적에게 신성피해를 입히고 9초간
	대상이 자신에게 입히는 피해를 25%만큼 감소시킴
	*/

	hitCollider = new SphereCollider();
	hitCollider->SetActive(false);

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 0.0f;

		// 스킬 데미지
		skillDamage = 100.0f;

		// 쿨타임 설정
		MAX_delay = 0.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// // 마나 소모 불명 : 0.5%
	}

	// 이펙트를 위한 변수?
	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	// 이펙트 텍스처
	donut = new Quad(L"Textures/Effect/alpha_gold_donut.png");
	donut->SetParent(hitCollider);
	donut->Scale() *= 0.1;

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/032.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "P_024_Guardian_Of_Ancient_Kings";
}

P_032_Eye_Of_Tyr::~P_032_Eye_Of_Tyr()
{
	delete donut;
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete targetCharcter;

	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void P_032_Eye_Of_Tyr::Update()
{
	//ActiveSkill::Update();

	if (isRun)
	{
		hitCollider->Pos() = owner->GlobalPos();
		 
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

		float ful = 10.5f; // 값 변경을 쉽게 하기 위한 변수
		hitCollider->Scale().x += ful * DELTA;
		hitCollider->Scale().y += ful * DELTA;
		hitCollider->Scale().z += ful * DELTA;

		// 히트 범위가 일정 수준을 넘어가면 액티브를 끄면서 동작 정지
		if (hitCollider->Scale().x >= 7)
		{
			hitCollider->SetActive(false);
			//hitCollider->Scale() = Vector3(1, 1, 1);
			isRun = false;
		}

		donut->Rot() = CAM->Rot();
		donut->UpdateWorld();
		hitCollider->UpdateWorld();
	}
	else if (!isRun)
	{
		hitCollider->Scale() = Vector3(1, 1, 1);
		hitCollider->Pos() = Vector3(0, -50, 0);
		hitCollider->UpdateWorld();
		donut->UpdateWorld();
	}

	ActiveSkill::Cooldown();
}

void P_032_Eye_Of_Tyr::Render()
{
	if (isRun)
	{
		blendState[1]->SetState();
		depthState[1]->SetState();

		donut->Render();

		blendState[0]->SetState();
		depthState[0]->SetState();

		//hitCollider->Render();
	}
}

void P_032_Eye_Of_Tyr::UseSkill()
{
	if (isCooldown) return;

	hitCollider->SetActive(true);
	isRun = true;
	isCooldown = true;
}