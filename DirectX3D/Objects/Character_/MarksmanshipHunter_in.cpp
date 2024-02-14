#include "Framework.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"

MarksmanshipHunter_in::MarksmanshipHunter_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	: CH_Base_ver2(type, ProfessionType::ProtectionWarrior)
{
	transform->SetParent(this);
	this->instancing = instancing;
	this->index = index;

	myCollider = new CapsuleCollider(0.5f, 1.0f);
	myCollider->SetParent(this);
	myCollider->Pos() = Vector3(0, 1.0f, 0);

	motion = instancing->GetMotion(index);
	totalEvents.resize(instancing->GetClipSize());
	eventIters.resize(instancing->GetClipSize());

	SetEvent(ATTACK1, bind(&MarksmanshipHunter_in::EndATK, this), 0.7f);
	SetEvent(HIT, bind(&MarksmanshipHunter_in::EndHit, this), 0.9f);
	SetEvent(DIE, bind(&MarksmanshipHunter_in::EndDie, this), 1);

	// 자신의 타입에 따라 
	switch (creatureType)
	{
	case CreatureType::Player:
		range = new SphereCollider(10);
		break;

	case CreatureType::NonPlayer:
		range = new SphereCollider(20);
		break;
	}
	range->SetParent(this);

	FOR(totalEvents.size())
	{
		eventIters[i] = totalEvents[i].begin();
	}
	this->SetActive(true);

	mainHandBoneIndex = 23;
	FOR(7)
	{
		// 공격 판별용 bool 벡터 변수
		// 0 = 일반공격
		// 1 = 조준 사격
		// 2 = 속사
		// 3 = 키메라 사격
		// 4 = 일제 사격
		// 5 = 연발 사격
		// 6 = 울부짖는 화살
		attackSignal.push_back(false);
	}
	skillList.push_back(new M_000_Basic_Atttack());
	skillList[skillList.size() - 1]->SetOwner(this);
}

MarksmanshipHunter_in::~MarksmanshipHunter_in()
{
	delete instancing;
	delete motion;
	delete myCollider;
	delete range;

	for (SkillBase* skill : skillList)
		delete skill;
}

void MarksmanshipHunter_in::Update()
{
	// 액티브 상태가 아니라면 업데이트하지 않음
	if (!Active()) return;

	// 플레이어 타입에 따라 업데이트 수행
	switch (creatureType)
	{
	case CreatureType::Player:
		PlayerUpdate();
		break;

	case CreatureType::NonPlayer:
		AIUpdate();
		break;
	}

	FOR(skillList.size())
		skillList[i]->Update();

	ExecuteEvent();
	CH_Base_ver2::Update();
	Transform::UpdateWorld();
}

void MarksmanshipHunter_in::Render()
{
	// 액티브 상태가 아니라면 업데이트하지 않음
	if (!Active()) return;

	myCollider->Render();
	range->Render();

	FOR(skillList.size())
		skillList[i]->Render();

	CH_Base_ver2::Render();
}

void MarksmanshipHunter_in::EquipWeapon(Weapon* weapon)
{
	if (weapon == nullptr) return;

	this->weapon = weapon;
	weapon->Rot() = Vector3(0.0f, 21.0f, 20.0f);
	weapon->SetParent(mainHand);
}

void MarksmanshipHunter_in::PlayerUpdate()
{
	Control();
	//Casting();

	// 충돌체 업데이트
	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void MarksmanshipHunter_in::AIUpdate()
{
	if (!myPlayer) return;
	AI_animation_Moving();

	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void MarksmanshipHunter_in::OnHit(float damage)
{
	stat.hp -= damage;

	if (stat.hp > 0)
	{
		SetState(HIT);
	}
	else if (stat.hp <= 0)
	{
		SetState(DIE);
	}

}

void MarksmanshipHunter_in::AI_animation_Moving()
{
	// 내가 플레이어의 주위에 있다면
	if (myPlayer->GetRange()->IsCollision(myCollider))
	{
		randomHangdong -= DELTA;
		if (randomHangdong <= 0)
		{
			randomHangdong = MAX_randomHangdong;
			randomVelocity = Vector3(Random(-1, 2), 0, Random(-1, 2));
		}

		this->Pos() += randomVelocity * (moveSpeed / 10) * DELTA;
		this->Rot().y = atan2(randomVelocity.x, randomVelocity.z) + XM_PI;

		SetState(WALK_F);
	}
	// 플레이어의 주변이 아니라면
	else
	{
		Vector3 velo = (myPlayer->Pos() - this->Pos()).GetNormalized();
		randomVelocity = velo;
		randomHangdong = 2.0f;

		this->Rot().y = atan2(velo.x, velo.z) + XM_PI;

		this->Pos() += velo * moveSpeed * DELTA;
		SetState(WALK_F);
	}
}

void MarksmanshipHunter_in::Control()
{
	Moving();

	if (KEY_DOWN(VK_SPACE) && !isJump)
	{
		if (curState == IDLE1 || curState == WALK_F || curState == WALK_B || curState == WALK_L || curState == WALK_R)
		{
			SetState(JUMP);
			jumpVelocity = jumpForce;
			isJump = true;
		}
	}

	Attack();
	Jump();
}

void MarksmanshipHunter_in::Moving()
{
	// 점프, 공격, 맞을 때, 죽었을 경우 움직이지 않기
	if (curState == ATTACK1 || curState == DIE || curState == HIT ||
		curState == SKILL1 || curState == SKILL2) return;

	bool isMoveZ = false;
	bool isMoveX = false;

	// 캐릭터 기본 이동 : W(앞), S(뒤), Q(좌), E(우)
	{
		if (KEY_PRESS('W'))
		{
			velocity.z += DELTA;
			isMoveZ = true;
		}
		if (KEY_PRESS('S'))
		{
			velocity.z -= DELTA;
			isMoveZ = true;
		}
		if (KEY_PRESS('Q'))
		{
			velocity.x -= DELTA;
			isMoveX = true;
		}
		if (KEY_PRESS('E'))
		{
			velocity.x += DELTA;
			isMoveX = true;
		}
	}

	// 캐릭터 마우스 우클릭에 따른 이동 변화
	{
		if (KEY_PRESS(VK_RBUTTON))
		{
			// 좌우 이동
			if (KEY_PRESS('A'))
			{
				velocity.x -= DELTA;
				isMoveX = true;
			}
			if (KEY_PRESS('D'))
			{
				velocity.x += DELTA;
				isMoveX = true;
			}
		}
		else
		{
			// 앞뒤로 이동 중이 아닐 때
			if (KEY_PRESS('W') || KEY_PRESS('S'))
			{
				// 좌우 회전
				if (KEY_PRESS('A'))
				{
					Rot().y -= turnSpeed * DELTA;
				}
				if (KEY_PRESS('D'))
				{
					Rot().y += turnSpeed * DELTA;
				}
			}
		}
	}

	// 가속도 설정
	if (velocity.Length() > 1) velocity.Normalize();
	if (!isMoveZ) velocity.z = Lerp(velocity.z, 0, deceleration * DELTA);
	if (!isMoveX) velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY);

	// 위치 이동
	this->Pos() += direction * -1 * moveSpeed * DELTA;

	// 점프인 경우라면 애니메이션 설정 X
	if (curState == JUMP) return;

	if (velocity.z > 0.1f)
		SetState(WALK_F);
	else if (velocity.z < -0.1f)
		SetState(WALK_B);
	else if (velocity.x < -0.1f)
		SetState(WALK_L);
	else if (velocity.x > 0.1f)
		SetState(WALK_R);
	else
		SetState(IDLE1);
}

void MarksmanshipHunter_in::Jump()
{
	// 점프중이 아니라면 리턴
	if (!isJump) return;

	jumpVelocity -= 1.8f * gravityMult * DELTA;
	Pos().y += jumpVelocity;

	// 현재의 지정 높이보다 위치가 낮다면?
	if (Pos().y < curheight)
	{
		// 위치 초기화 및 상태 전환
		Pos().y = curheight;
		jumpVelocity = 0;
		SetState(IDLE1);
		isJump = false;
	}
}

void MarksmanshipHunter_in::Attack()
{
	// 점프, 사망, 피격, 공격 상태인 경우 리턴
	if (curState == JUMP || curState == DIE || curState == HIT || curState == ATTACK1) return;

	if (attackSignal[0])
	{
		attackSignal[0] = false;

		// TODO : 원거리 공격 만들기
		skillList[0]->UseSkill(monsterSelectData);
	}
}

void MarksmanshipHunter_in::SetState(State state)
{
	if (state == curState) return;
	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvents[state].begin();
}

void MarksmanshipHunter_in::EndATK()
{
	SetState(IDLE1);
}

void MarksmanshipHunter_in::EndHit()
{
	if (stat.hp <= 0)
	{
		SetState(DIE);
	}
}

void MarksmanshipHunter_in::EndDie()
{
	SetActive(false);
}

void MarksmanshipHunter_in::EndCasting()
{
	SetState(IDLE1);
}

void MarksmanshipHunter_in::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void MarksmanshipHunter_in::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}