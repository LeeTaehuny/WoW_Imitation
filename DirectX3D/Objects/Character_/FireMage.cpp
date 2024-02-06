#include "Framework.h"

FireMage::FireMage(CreatureType type) : CH_Base("FireMage", type, ProfessionType::FireMage)
{
	ReadClip("Idle_1");
	ReadClip("Idle_2");
	ReadClip("Attack_1");
	ReadClip("Attack_2");
	ReadClip("Attack_3");
	ReadClip("Walk_F");
	ReadClip("Walk_B");
	ReadClip("Walk_L");
	ReadClip("Walk_R");
	ReadClip("Die_1");
	ReadClip("Die_2");
	ReadClip("Hit_1");
	ReadClip("Hit_2");
	ReadClip("Jump");

	GetClip((int)ATTACK1)->SetEvent(bind(&FireMage::EndATK, this), 0.7f);
	GetClip((int)ATTACK2)->SetEvent(bind(&FireMage::EndATK, this), 0.7f);
	GetClip((int)ATTACK3)->SetEvent(bind(&FireMage::EndATK, this), 0.7f);
	
	GetClip((int)HIT1)->SetEvent(bind(&FireMage::EndHit, this), 0.6f);
	GetClip((int)HIT2)->SetEvent(bind(&FireMage::EndHit, this), 0.6f);
	GetClip((int)DIE1)->SetEvent(bind(&FireMage::EndDie, this), 0.9f);
	GetClip((int)DIE2)->SetEvent(bind(&FireMage::EndDie, this), 0.9f);

	Scale() *= 0.01f;

	collider = new CapsuleCollider(0.5f, 1.5f);
	collider->SetParent(this);
	collider->Pos() = Vector3(0, 100.0f, 0);
	collider->Scale() *= 100;
}

FireMage::~FireMage()
{
	delete collider;
}

void FireMage::Update()
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

void FireMage::Render()
{
	// 액티브 상태가 아니라면 업데이트하지 않음
	if (!Active()) return;

	collider->Render();
	CH_Base::Render();
}

void FireMage::PlayerUpdate()
{
	Control();
	//Casting();

	// 충돌체 업데이트
	collider->UpdateWorld();
}

void FireMage::AIUpdate()
{
}

void FireMage::Control()
{
	Moving();

	if (KEY_DOWN(VK_SPACE) && !isJump)
	{
		if (curState == IDLE1 || curState == IDLE2 || curState == WALK_F || curState == WALK_B || curState == WALK_L || curState == WALK_R)
		{
			SetState(JUMP);
			jumpVelocity = jumpForce;
			isJump = true;
		}
	}

	Attack();
	Jump();
}

void FireMage::Moving()
{
	// 점프, 공격, 히트, 죽었을 때 움직이지 않음
	if (curState == ATTACK1 || curState == ATTACK2 || curState == ATTACK3 || curState == DIE1 || curState == DIE2) return;
	if (curState == HIT1 || curState == HIT2) return;

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

void FireMage::Jump()
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

void FireMage::Attack()
{
	// 점프, 사망, 피격, 공격 상태인 경우 리턴
	if (curState == JUMP || curState == DIE1 || curState == DIE2 || curState == HIT1 || curState == HIT2 || curState == ATTACK1 || curState == ATTACK2 || curState == ATTACK3) return;

	// 좌클릭 시 공격 설정
	if (KEY_DOWN(VK_LBUTTON))
	{
		int atk_ran = Random(1, 4);

		if (atk_ran == 1)
		{
			SetState(ATTACK1);
		}
		else if (atk_ran == 2)
		{
			SetState(ATTACK2);
		}
		else if (atk_ran == 3)
		{
			SetState(ATTACK3);
		}
	}
}

void FireMage::SetState(State state)
{
	if (curState == state) return;

	curState = state;
	PlayClip(state);
}

//void FireMage::Casting()
//{
//	if (isCasting)
//	{
//		isCasting = false;
//		int atk_ran = Random(1, 4);
//
//		if (atk_ran == 1)
//		{
//			SetState(ATTACK1);
//		}
//		else if (atk_ran == 2)
//		{
//			SetState(ATTACK2);
//		}
//		else if (atk_ran == 3)
//		{
//			SetState(ATTACK3);
//		}
//	}
//}

void FireMage::OnHit(Collider* collider)
{
	if (this->collider->IsCollision(collider))
	{
		int hd_value = Random(1, 3);

		if (cur_hp > 0)
		{
			if (hd_value == 1) SetState(HIT1);
			else if (hd_value == 2) SetState(HIT2);
			
		}
		else if (cur_hp <= 0)
		{
			if (hd_value == 1) SetState(DIE1);
			else if (hd_value == 2) SetState(DIE2);
		}
	}
}

void FireMage::EndATK()
{
	SetState(IDLE1);
}

void FireMage::EndHit()
{
	if (cur_hp <= 0)
	{
		int hd_value = Random(1, 3);

		if (hd_value == 1) SetState(DIE1);
		else if (hd_value == 2) SetState(DIE2);
	}
}

void FireMage::EndDie()
{
	SetActive(false);
}

//void FireMage::EndCasting()
//{
//	isCasting = false;
//	SetState(IDLE1);
//}