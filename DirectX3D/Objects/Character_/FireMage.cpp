#include "Framework.h"

FireMage::FireMage() : CH_Base("FireMage")
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
	
	GetClip((int)JUMP)->SetEvent(bind(&FireMage::EndJUMP, this), 0.6f);
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

void FireMage::Moving()
{
	// 점프, 공격 죽일때 움직이지 않음
	if (isJump) return;
	if (INTstate == (int)ATTACK1) return;
	if (INTstate == (int)ATTACK2) return;
	if (INTstate == (int)ATTACK3) return;
	if (INTstate == (int)DIE1) return;
	if (INTstate == (int)DIE2) return;

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

void FireMage::Jump()
{
	if (INTstate == (int)DIE1) return;
	if (INTstate == (int)DIE2) return;

	if (KEY_DOWN(VK_SPACE))
	{
		SetState(JUMP);
		isJump = true;
	}
}

void FireMage::Attack()
{
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

void FireMage::Casting()
{
	if (isCasting)
	{
		isCasting = false;
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

void FireMage::EndJUMP()
{
	SetState(IDLE1);
	isJump = false;
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

void FireMage::EndCasting()
{
	isCasting = false;
	SetState(IDLE1);
}