#include "Framework.h"

P_001_Avengers_Shield::P_001_Avengers_Shield() : ActiveSkill(SkillType::Target)
{
	/*
	스킬의 효과

	적에게 방패를 던짐
	*/

	// 콜라이더 생성 후 바로 비활성화
	myCollider = new SphereCollider();
	myCollider->SetActive(false);
	hitCollider = new SphereCollider();
	hitCollider->SetActive(false);

	Yad = new SphereCollider(60);
	// 야드 콜라이더를 마이너스 3000 좌표로 날림
	// 첫 시도할 때 적이 좌표 0, 0, 0 에 있으면 무조건 발동되버리는 것에 대한 조치
	Yad->Pos() = Vector3(0, -3000);
	Yad->SetActive(false);
	Yad->UpdateWorld();

	// 스킬 속도
	speed = 30.0f;

	// 스킬 데미지
	skillDamage = 100.0f;

	// 쿨타임 설정 (5초)
	MAX_delay = 5.0f;
	coolTime = MAX_delay;

	// 처음은 스킬 실행중인 상태가 아니도록 설정
	isRun = false;
	isCooldown = false;

	shielD = new Model("shield");
	shielD->Scale() *= 2;
	shielD->SetParent(myCollider);

	three.resize(3);

	startEdge = new Transform();
	endEdge = new Transform();
	trail = new Trail(L"Textures/Effect/alpha_white.png", startEdge, endEdge, 50, 125.0f);

	// 스킬 아이콘 이미지 저장
	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/001.jpg");
}
P_001_Avengers_Shield::~P_001_Avengers_Shield()
{
	delete Yad;
	delete shielD;
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete startEdge;
	delete endEdge;
	delete trail;
	for (Collider* col : three)
		delete col;
}

void P_001_Avengers_Shield::Update()
{
	Yad->UpdateWorld();

	target = three[impaction_count];
	if (isRun)
	{
		ActiveSkill::Update();

		shielD->Rot().x = atan2(direction.z, direction.y) + XM_PI;
		shielD->Rot().z += 20 * DELTA;

		shielD->UpdateWorld();
		myCollider->UpdateWorld();
		hitCollider->UpdateWorld();

		{
			startEdge->Pos() = myCollider->GlobalPos() + myCollider->Left() * 0.5f;
			endEdge->Pos() = myCollider->GlobalPos() + myCollider->Right() * 0.5f;

		}
	}
	else
	{
		startEdge->Pos() = owner->GlobalPos();
		endEdge->Pos() = owner->GlobalPos();
	}

	startEdge->UpdateWorld();
	endEdge->UpdateWorld();
	trail->Update();
	Impact();

	// 작동중인 상태와 쿨타임을 분리하여 던져지자 마자 쿨이 돌도록 수정
	if (isCooldown)
	{
		ActiveSkill::Cooldown();
	}
}

void P_001_Avengers_Shield::Render()
{
	myCollider->Render();
	Yad->Render();

	// 콜라이더가 활성화 상태일때만 보임
	if (myCollider->Active())
	{
		shielD->Render();
		trail->Render();
	}
}

void P_001_Avengers_Shield::UseSkill(Collider* targetCollider)
{
	if (!isCooldown && targetCollider == nullptr) return;
	three[0] = targetCollider;
	target = three[0];

	Yad->SetActive(true);
	Yad->Pos() = owner->Pos();
	Yad->UpdateWorld();
	if (Yad->IsCollision(target))
	{
		if (!isCooldown)
		{
			myCollider->SetActive(true);
			myCollider->Pos() = owner->GlobalPos();
			isRun = true;
			isCooldown = true;

			startEdge->Pos() = myCollider->GlobalPos() + myCollider->Forward() * 1.0f;
			endEdge->Pos() = myCollider->GlobalPos() + myCollider->Back() * 1.0f;
			startEdge->UpdateWorld();
			endEdge->UpdateWorld();
		}
	}
}

void P_001_Avengers_Shield::Impact()
{
	// 몬스터 자체의 수가 0마리 이하라면 그냥 리턴
	if (MONSTER->GetSkeleton().size() <= 0 &&
		MONSTER->GetSkeleton_Knight().size() <= 0 &&
		MONSTER->GetScarecrow().size() <= 0)
	{
		impaction_count = 0;
		return;
	}

	vector<MonsterBase*> monster;

	if (impact && impaction_count == 0)
	{
		impact = false;
		impaction_count++;
		Yad->Pos() = myCollider->Pos();

		// 가장 거리가 짧은 값을 저장하기 위한 함수, 최대값을 줌
		float min_length = FLT_MAX;
		monster = MONSTER->GetSkeleton();
		for (int i = 0; i < monster.size(); ++i)
		{
			// 0번에 저장된 값과 같은 것이라면 다음으로 진행
			// 그리고 거리콜라이더와 충돌한 콜라이더만 연산
			if (three[0] == monster[i]->GetCollider() ||
				!Yad->IsCollision(monster[i]->GetCollider())) continue;

			// 몬스터 콜라이더의 위치값과 지금 타격한 대상의 위치 값의 차를 구함
			Vector3 im = monster[i]->GetCollider()->GlobalPos() - three[0]->GlobalPos();
			// 구한 차이값의 거리를 저장
			float length = abs(im.Length());

			// 저장된 거리 값중 가장 작거나 같은 값을 계속해서 저장함
			// 마찬가지로 포인터에 값도 저장
			if (min_length >= length)
			{
				min_length = length;
				three[1] = monster[i]->GetCollider();
				myCollider->SetActive(true);

				isRun = true;
			}
		}
		monster = MONSTER->GetSkeleton_Knight();
		for (int i = 0; i < monster.size(); ++i)
		{
			// 0번에 저장된 값과 같은 것이라면 다음으로 진행
			// 그리고 거리콜라이더와 충돌한 콜라이더만 연산
			if (three[0] == monster[i]->GetCollider() ||
				!Yad->IsCollision(monster[i]->GetCollider())) continue;

			// 몬스터 콜라이더의 위치값과 지금 타격한 대상의 위치 값의 차를 구함
			Vector3 im = monster[i]->GetCollider()->GlobalPos() - three[0]->GlobalPos();
			// 구한 차이값의 거리를 저장
			float length = abs(im.Length());

			// 저장된 거리 값중 가장 작거나 같은 값을 계속해서 저장함
			// 마찬가지로 포인터에 값도 저장
			if (min_length >= length)
			{
				min_length = length;
				three[1] = monster[i]->GetCollider();
				myCollider->SetActive(true);

				isRun = true;
			}
		}
		monster = MONSTER->GetScarecrow();
		for (int i = 0; i < monster.size(); ++i)
		{
			// 0번에 저장된 값과 같은 것이라면 다음으로 진행
			// 그리고 거리콜라이더와 충돌한 콜라이더만 연산
			if (three[0] == monster[i]->GetCollider() ||
				!Yad->IsCollision(monster[i]->GetCollider())) continue;

			// 몬스터 콜라이더의 위치값과 지금 타격한 대상의 위치 값의 차를 구함
			Vector3 im = monster[i]->GetCollider()->GlobalPos() - three[0]->GlobalPos();
			// 구한 차이값의 거리를 저장
			float length = abs(im.Length());

			// 저장된 거리 값중 가장 작거나 같은 값을 계속해서 저장함
			// 마찬가지로 포인터에 값도 저장
			if (min_length >= length)
			{
				min_length = length;
				three[1] = monster[i]->GetCollider();
				myCollider->SetActive(true);

				isRun = true;
			}
		}

		if (min_length == FLT_MAX)
		{
			impaction_count = 0;
			isRun = false;
		}
	}
	else if (impact && impaction_count == 1)
	{
		impact = false;
		// 위 업데이트 문에서 에너미의 콜라이더 포인터 값을 바꾸기 위한 누적연산자
		impaction_count++;
		// 충돌한 내 자신의 콜라이더의 위치를 받아옴
		Yad->Pos() = myCollider->Pos();

		float min_length = FLT_MAX;
		monster = MONSTER->GetSkeleton();
		for (int i = 0; i < monster.size(); ++i)
		{
			// 0번에 저장된 값과 같은 것이라면 다음으로 진행
			// 그리고 거리콜라이더와 충돌한 콜라이더만 연산
			if (three[0] == monster[i]->GetCollider() ||
				three[1] == monster[i]->GetCollider() ||
				!Yad->IsCollision(monster[i]->GetCollider())) continue;

			// 몬스터 콜라이더의 위치값과 지금 타격한 대상의 위치 값의 차를 구함
			Vector3 im = monster[i]->GetCollider()->GlobalPos() - three[1]->GlobalPos();
			// 구한 차이값의 거리를 저장
			float length = abs(im.Length());

			// 저장된 거리 값중 가장 작거나 같은 값을 계속해서 저장함
			// 마찬가지로 포인터에 값도 저장
			if (min_length >= length)
			{
				min_length = length;
				three[2] = monster[i]->GetCollider();
				myCollider->SetActive(true);

				isRun = true;
			}
		}
		monster = MONSTER->GetSkeleton_Knight();
		for (int i = 0; i < monster.size(); ++i)
		{
			// 0번에 저장된 값과 같은 것이라면 다음으로 진행
			// 그리고 거리콜라이더와 충돌한 콜라이더만 연산
			if (three[0] == monster[i]->GetCollider() ||
				three[2] == monster[i]->GetCollider() ||
				!Yad->IsCollision(monster[i]->GetCollider())) continue;

			// 몬스터 콜라이더의 위치값과 지금 타격한 대상의 위치 값의 차를 구함
			Vector3 im = monster[i]->GetCollider()->GlobalPos() - three[1]->GlobalPos();
			// 구한 차이값의 거리를 저장
			float length = abs(im.Length());

			// 저장된 거리 값중 가장 작거나 같은 값을 계속해서 저장함
			// 마찬가지로 포인터에 값도 저장
			if (min_length >= length)
			{
				min_length = length;
				three[2] = monster[i]->GetCollider();
				myCollider->SetActive(true);

				isRun = true;
			}
		}
		monster = MONSTER->GetScarecrow();
		for (int i = 0; i < monster.size(); ++i)
		{
			// 0번에 저장된 값과 같은 것이라면 다음으로 진행
			// 그리고 거리콜라이더와 충돌한 콜라이더만 연산
			if (three[0] == monster[i]->GetCollider() ||
				three[1] == monster[i]->GetCollider() ||
				!Yad->IsCollision(monster[i]->GetCollider())) continue;

			// 몬스터 콜라이더의 위치값과 지금 타격한 대상의 위치 값의 차를 구함
			Vector3 im = monster[i]->GetCollider()->GlobalPos() - three[1]->GlobalPos();
			// 구한 차이값의 거리를 저장
			float length = abs(im.Length());

			// 저장된 거리 값중 가장 작거나 같은 값을 계속해서 저장함
			// 마찬가지로 포인터에 값도 저장
			if (min_length >= length)
			{
				min_length = length;
				three[2] = monster[i]->GetCollider();
				myCollider->SetActive(true);

				isRun = true;
			}
		}

		if (min_length == FLT_MAX)
		{
			impaction_count = 0;
			isRun = false;
		}
	}
	else if (impact)
	{
		impact = false;
		isRun = false;
		// 값이 2인 상태에서 또 충돌이 일어났다면 다시 카운트를 0으로 변경
		impaction_count = 0;
		myCollider->SetActive(false);
	}
}
