#include "Framework.h"

MarksmanshipHunter::MarksmanshipHunter(int myNober) : CH_Base("MarksmanshipHunter", myNober)
{
	ReadClip("Idle");
	ReadClip("Attack_1");
	ReadClip("Walk_F");
	ReadClip("Walk_B");
	ReadClip("Walk_L");
	ReadClip("Walk_R");
	ReadClip("Die");
	ReadClip("Hit");
	ReadClip("Jump");
	ReadClip("S_Dive");
	ReadClip("S_Shooting");

	GetClip((int)ATTACK1)->SetEvent(bind(&MarksmanshipHunter::EndATK, this), 0.3f);

	GetClip((int)JUMP)->SetEvent(bind(&MarksmanshipHunter::EndJUMP, this), 0.6f);
	GetClip((int)HIT)->SetEvent(bind(&MarksmanshipHunter::EndHit, this), 0.6f);
	GetClip((int)DIE)->SetEvent(bind(&MarksmanshipHunter::EndDie, this), 0.9f);

	GetClip((int)SKILL1)->SetEvent(bind(&MarksmanshipHunter::EndCasting, this), 0.9f);
	//GetClip((int)SKILL2)->SetEvent(bind(&MarksmanshipHunter::EndCasting, this), 0.9f);

	collider = new CapsuleCollider(0.5f, 1.3f);
	collider->SetParent(this);
	collider->Pos() = Vector3(0, 1.0f, 0);
}

MarksmanshipHunter::~MarksmanshipHunter()
{
	delete collider;
}

void MarksmanshipHunter::Moving()
{
	// 점프, 공격 죽일때 움직이지 않음
	if (isJump) return;
	if (INTstate == (int)ATTACK1) return;
	if (INTstate == (int)DIE) return;
	if (INTstate == (int)SKILL1) return;
	if (INTstate == (int)SKILL2) return;

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
		SetState(IDLE1);
	}
}

void MarksmanshipHunter::Jump()
{
	if (INTstate == (int)DIE) return;

	if (KEY_DOWN(VK_SPACE))
	{
		SetState(JUMP);
		isJump = true;
	}
}

void MarksmanshipHunter::Attack()
{
	if (INTstate == (int)DIE) return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		int atk_ran = Random(1, 2);

		if (atk_ran == 1)
		{
			SetState(ATTACK1);
		}
	}
}

void MarksmanshipHunter::Casting()
{
	if (isCasting)
	{
		isCasting = false;
		int castValue = Random(1, 3);

		if (castValue == 1)
		{
			SetState(SKILL1);
		}
	}
}

void MarksmanshipHunter::OnHit(Collider* collider)
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

void MarksmanshipHunter::EndATK()
{
	SetState(IDLE1);
}

void MarksmanshipHunter::EndJUMP()
{
	SetState(IDLE1);
	isJump = false;
}

void MarksmanshipHunter::EndHit()
{
	if (cur_hp <= 0)
	{
		SetState(DIE);
	}
}

void MarksmanshipHunter::EndDie()
{
	SetActive(false);
}

void MarksmanshipHunter::EndCasting()
{
	isCasting = false;
	SetState(IDLE1);
}