#include "Framework.h"

HolyPriest::HolyPriest(CreatureType type) 
	: CH_Base("HolyPriest", type, ProfessionType::HolyPriest)
{
	ReadClip("Idle_1");
	ReadClip("Idle_2");
	ReadClip("Idle_3");
	ReadClip("Attack_1");
	ReadClip("Attack_2");
	ReadClip("Walk_F");
	ReadClip("Walk_B");
	ReadClip("Walk_L");
	ReadClip("Walk_R");
	ReadClip("Die");
	ReadClip("Hit");
	ReadClip("Jump");

	GetClip((int)ATTACK1)->SetEvent(bind(&HolyPriest::EndATK, this), 0.7f);
	GetClip((int)ATTACK2)->SetEvent(bind(&HolyPriest::EndATK, this), 0.7f);

	GetClip((int)HIT)->SetEvent(bind(&HolyPriest::EndHit, this), 0.6f);
	GetClip((int)DIE)->SetEvent(bind(&HolyPriest::EndDie, this), 0.9f);

	collider = new CapsuleCollider(0.4f, 0.7f);
	collider->SetParent(this);
	collider->Pos() = Vector3(0, 0.7f, 0);
}

HolyPriest::~HolyPriest()
{
	delete collider;
}

void HolyPriest::Update()
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

	CH_Base::Update();
}

void HolyPriest::Render()
{
	// 액티브 상태가 아니라면 업데이트하지 않음
	if (!Active()) return;

	collider->Render();
	CH_Base::Render();
}

void HolyPriest::PlayerUpdate()
{
	Control();
	//Casting();

	// 충돌체 업데이트
	collider->UpdateWorld();
}

void HolyPriest::AIUpdate()
{
}

void HolyPriest::Control()
{
	Moving();

	if (KEY_DOWN(VK_SPACE) && !isJump)
	{
		if (curState == IDLE1 || curState == IDLE2 || curState == IDLE3 || curState == WALK_F || curState == WALK_B || curState == WALK_L || curState == WALK_R)
		{
			SetState(JUMP);
			jumpVelocity = jumpForce;
			isJump = true;
		}
	}

	Attack();
	Jump();
}

void HolyPriest::Moving()
{
	// 점프, 공격, 맞을 때, 죽었을 경우 움직이지 않기
	if (curState == ATTACK1 || curState == ATTACK2 || curState == DIE || curState == HIT) return;

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
	Pos() += direction * -1 * moveSpeed * DELTA;

	// 점프인 경우라면 애니메이션 설정 X
	if (curState == JUMP) return;

	// 점프가 아닌 경우 속력값에 따라 애니메이션 설정
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

void HolyPriest::Jump()
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
		SetState(IDLE2);
		isJump = false;
	}
}

void HolyPriest::Attack()
{
	// 점프, 사망, 피격, 공격 상태인 경우 리턴
	if (curState == JUMP || curState == DIE || curState == HIT || curState == ATTACK1 || curState == ATTACK2) return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		int atk_ran = Random(1, 3);

		if (atk_ran == 1)
		{
			SetState(ATTACK1);
		}
		else if (atk_ran == 2)
		{
			SetState(ATTACK2);
		}
	}
}

void HolyPriest::SetState(State state)
{
	if (curState == state) return;

	curState = state;
	PlayClip(state);
}

//void HolyPriest::Casting()
//{
//	if (isCasting)
//	{
//		isCasting = false;
//		int atk_ran = Random(1, 3);
//
//		if (atk_ran == 1)
//		{
//			SetState(ATTACK1);
//		}
//		else if (atk_ran == 2)
//		{
//			SetState(ATTACK2);
//		}
//	}
//}

void HolyPriest::OnHit(Collider* collider)
{
	if (this->collider->IsCollision(collider))
	{
		if (cur_hp > 0)
		{
			SetState(HIT);
		}
		else if (cur_hp <= 0)
		{
			SetState(DIE);
		}
	}
}

void HolyPriest::EndATK()
{
	SetState(IDLE1);
}

void HolyPriest::EndHit()
{
	if (cur_hp <= 0)
	{
		SetState(DIE);
	}
}

void HolyPriest::EndDie()
{
	SetActive(false);
}

//void HolyPriest::EndCasting()
//{
//	isCasting = false;
//	SetState(IDLE1);
//}