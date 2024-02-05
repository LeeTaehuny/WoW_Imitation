#include "Framework.h"

ArmsWarrior::ArmsWarrior(CreatureType type) 
	: CH_Base("ArmsWarrior", type, ProfessionType::ArmsWarrior)
{
	ReadClip("Idle_1");
	ReadClip("Idle_2");
	ReadClip("Attack_1");
	ReadClip("Attack_2");
	ReadClip("Walk_F");
	ReadClip("Walk_B");
	ReadClip("Walk_L");
	ReadClip("Walk_R");
	ReadClip("Die");
	ReadClip("Hit");
	ReadClip("Jump");

	GetClip((int)ATTACK1)->SetEvent(bind(&ArmsWarrior::EndATK, this), 0.7f);
	GetClip((int)ATTACK2)->SetEvent(bind(&ArmsWarrior::EndATK, this), 0.7f);
	GetClip((int)JUMP)->SetEvent(bind(&ArmsWarrior::EndJUMP, this), 0.6f);

	GetClip((int)HIT)->SetEvent(bind(&ArmsWarrior::EndHit, this), 0.6f);
	GetClip((int)DIE)->SetEvent(bind(&ArmsWarrior::EndDie, this), 0.9f);

	collider = new CapsuleCollider(0.5f, 1.7f);
	collider->SetParent(this);
	collider->Pos() = Vector3(0, 1.5f, 0);
}

ArmsWarrior::~ArmsWarrior()
{
	delete collider;
}

void ArmsWarrior::Update()
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

void ArmsWarrior::Render()
{
	// 액티브 상태가 아니라면 업데이트하지 않음
	if (!Active()) return;

	collider->Render();
	CH_Base::Render();
}

void ArmsWarrior::PlayerUpdate()
{
	Moving();
	Jump();
	Attack();
	Casting();

	// 충돌체 업데이트
	collider->UpdateWorld();
}

void ArmsWarrior::AIUpdate()
{
}

void ArmsWarrior::Moving()
{
	// 점프, 공격 죽일때 움직이지 않음
	if (isJump) return;
	if (INTstate == (int)ATTACK1) return;
	if (INTstate == (int)ATTACK2) return;
	if (INTstate == (int)DIE) return;

	bool isMoveZ = false;
	bool isMoveX = false;
	float deceleration = 10;

	// 캐릭터 앞뒤좌우 이동입니다
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

	// 마우스 우클릭시 
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
	// 마우스 우클릭이 아닐때
	else
	{
		// 앞뒤로 이동 중이 아닐 때
		if (KEY_PRESS('W') || KEY_PRESS('S'))
		{
			// 좌우 회전
			float turnSpeed = 2;
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

	if (velocity.Length() > 1) velocity.Normalize();
	if (!isMoveZ) velocity.z = Lerp(velocity.z, 0, deceleration * DELTA);
	if (!isMoveX) velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

	if (velocity.z > 0.1f)
		SetState(WALK_F);
	else if (velocity.z < -0.1f)
		SetState(WALK_B);
	else if (velocity.x < -0.1f)
		SetState(WALK_L);
	else if (velocity.x > 0.1f)
		SetState(WALK_R);
	else
	{
		SetState(IDLE2);
	}
}

void ArmsWarrior::Jump()
{
	if (INTstate == (int)DIE) return;

	if (KEY_DOWN(VK_SPACE))
	{
		SetState(JUMP);
		isJump = true;
	}
}

void ArmsWarrior::Attack()
{
	if (INTstate == (int)DIE) return;

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

void ArmsWarrior::Casting()
{
	if (isCasting)
	{
		isCasting = false;
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

void ArmsWarrior::OnHit(Collider* collider)
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

void ArmsWarrior::EndATK()
{
	SetState(IDLE2);
}
void ArmsWarrior::EndJUMP()
{
	SetState(IDLE2);
	isJump = false;
}
void ArmsWarrior::EndHit()
{
	if (cur_hp <= 0)
	{
		SetState(DIE);
	}
}
void ArmsWarrior::EndDie()
{
	SetActive(false);
}

void ArmsWarrior::EndCasting()
{
	isCasting = false;
	SetState(IDLE1);
}