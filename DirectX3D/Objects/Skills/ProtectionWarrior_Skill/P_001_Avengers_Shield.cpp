#include "Framework.h"

P_001_Avengers_Shield::P_001_Avengers_Shield() : TargetSkill(BB)
{
	MAX_delay = 2;

	// 콜라이더 생성 후 바로 비활성화
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	Yad = new SphereCollider(60);
	// 야드 콜라이더를 마이너스 3000 좌표로 날림
	// 첫 시도할 때 적이 좌표 0, 0, 0 에 있으면 무조건 발동되버리는 것에 대한 조치
	Yad->Pos() = Vector3(0, -3000);
	Yad->SetActive(false);
	Yad->UpdateWorld();

	// 날아가는 속도 설정
	FlyingSpeed = 10;

	shielD = new Model("shield");
	shielD->Scale() *= 2;

	three.resize(3);
}
P_001_Avengers_Shield::~P_001_Avengers_Shield()
{
	delete Yad;
	delete shielD;
	for (Collider* col : three)
		delete col;
}

void P_001_Avengers_Shield::Update()
{
	Yad->UpdateWorld();

	enemy = three[impaction_count];
	if (isRun)
	{
		TargetSkill::Target();

		shielD->Pos() = myCollider->Pos();
		shielD->Rot().x = atan2(velocity.z, velocity.y) + XM_PI;
		shielD->Rot().z += 20 * DELTA;

		shielD->UpdateWorld();
		myCollider->UpdateWorld();
	}
	Impact();

	// 작동중인 상태와 쿨타임을 분리하여 던져지자 마자 쿨이 돌도록 수정
	if (isCooldown)
	{
		SkillBase::Cooldown();
	}
}

void P_001_Avengers_Shield::Render()
{
	//myCollider->Render();
	//Yad->Render();

	// 콜라이더가 활성화 상태일때만 보임
	if (myCollider->Active())
	{
		shielD->Render();
	}
}

void P_001_Avengers_Shield::UseSkill(Vector3 pos)
{
	if (!enemy) return;

	Yad->SetActive(true);
	Yad->Pos() = pos;
	if (Yad->IsCollision(enemy))
	{
		if (!isCooldown)
		{
			myCollider->SetActive(true);
			myCollider->Pos() = pos;
			isRun = true;
			isCooldown = true;
		}
	}
}

void P_001_Avengers_Shield::Impact()
{
	// 몬스터 자체의 수가 0마리 이하라면 그냥 리턴
	if (MONSTER->monsterCollider.size() <= 0)
	{
		impaction_count = 0;
		return;
	}

	if (impact && impaction_count == 0)
	{
		impact = false;
		// 위 업데이트 문에서 에너미의 콜라이더 포인터 값을 바꾸기 위한 누적연산자
		impaction_count++;
		// 충돌한 내 자신의 콜라이더의 위치를 받아옴
		Yad->Pos() = myCollider->Pos();
		
		// 가장 거리가 짧은 값을 저장하기 위한 함수, 최대값을 줌
		//int min_length = INT_MAX;
		float min_length = FLT_MAX;
		for (int i = 0; i < MONSTER->monsterCollider.size(); ++i)
		{
			// 0번에 저장된 값과 같은 것이라면 다음으로 진행
			// 그리고 거리콜라이더와 충돌한 콜라이더만 연산
			if (three[0] == MONSTER->monsterCollider[i] ||
				!Yad->IsCollision(MONSTER->monsterCollider[i])) continue;

			// 몬스터 콜라이더의 위치값과 지금 타격한 대상의 위치 값의 차를 구함
			Vector3 im = MONSTER->monsterCollider[i]->GlobalPos() - three[0]->GlobalPos();
			// 구한 차이값의 거리를 저장
			float length = abs(im.Length());

			// 저장된 거리 값중 가장 작거나 같은 값을 계속해서 저장함
			// 마찬가지로 포인터에 값도 저장
			if (min_length >= length)
			{
				min_length = length;
				three[1] = MONSTER->monsterCollider[i];
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

		// 가장 거리가 짧은 값을 저장하기 위한 함수, 최대값을 줌
		//float min_length = FLT_MAX;
		float min_length = FLT_MAX;
		for (int i = 0; i < MONSTER->monsterCollider.size(); ++i)
		{
			// 0번과 1번에 저장된 값과 같은 것이라면 다음으로 진행
			// 그리고 거리콜라이더와 충돌한 콜라이더만 연산
			if (three[0] == MONSTER->monsterCollider[i] ||
				three[1] == MONSTER->monsterCollider[i] ||
				!Yad->IsCollision(MONSTER->monsterCollider[i])) continue;

			// 몬스터 콜라이더의 위치값과 지금 타격한 대상의 위치 값의 차를 구함
			Vector3 im = MONSTER->monsterCollider[i]->GlobalPos() - three[0]->GlobalPos();
			// 구한 차이값의 거리를 저장
			float length = abs(im.Length());

			// 저장된 거리 값중 가장 작거나 같은 값을 계속해서 저장함
			// 마찬가지로 포인터에 값도 저장
			if (min_length >= length)
			{
				min_length = length;
				three[2] = MONSTER->monsterCollider[i];
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
		// 값이 2인 상태에서 또 충돌이 일어났다면 다시 카운트를 0으로 변경
		impaction_count = 0;
	}
}