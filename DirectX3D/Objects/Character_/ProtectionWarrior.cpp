#include "Framework.h"

ProtectionWarrior::ProtectionWarrior() : CH_Base("ProtectionWarrior")
{
	ReadClip("Idle_1");
	ReadClip("Idle_2");
	ReadClip("Idle_3");
	ReadClip("Attack_1");
	ReadClip("Walk_F");
	ReadClip("Walk_B");
	ReadClip("Walk_L");
	ReadClip("Walk_R");
	ReadClip("Die");
	ReadClip("Hit");
	ReadClip("Jump");
	ReadClip("S_Casting");

	GetClip((int)ATTACK1)->SetEvent(bind(&ProtectionWarrior::EndATK, this), 0.7f);

	GetClip((int)JUMP)->SetEvent(bind(&ProtectionWarrior::EndJUMP, this), 0.6f);

	GetClip((int)HIT)->SetEvent(bind(&ProtectionWarrior::EndHit, this), 0.6f);
	GetClip((int)DIE)->SetEvent(bind(&ProtectionWarrior::EndDie, this), 0.9f);

	GetClip((int)SKILL1)->SetEvent(bind(&ProtectionWarrior::EndCasting, this), 0.4f);

	collider = new CapsuleCollider(0.5f, 1.0f);
	collider->SetParent(this);
	collider->Pos() = Vector3(0, 1.0f, 0);
}

ProtectionWarrior::~ProtectionWarrior()
{
	delete collider;
}

void ProtectionWarrior::Moving()
{
	if (isJump) return;
	if (INTstate == (int)ATTACK1) return;
	if (INTstate == (int)DIE) return;
	if (INTstate == (int)SKILL1) return;

	bool isMoveZ = false;
	bool isMoveX = false;
	float deceleration = 10;

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

	if (KEY_PRESS(VK_RBUTTON))
	{
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
		if (KEY_PRESS('W') || KEY_PRESS('S'))
		{
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

void ProtectionWarrior::Jump()
{
	if (KEY_DOWN(VK_SPACE))
	{
		SetState(JUMP);
		isJump = true;
	}
}

void ProtectionWarrior::Attack()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		SetState(ATTACK1);
	}
}

void ProtectionWarrior::Casting()
{
	// 현재 스킬을 사용했다면
	if (isCasting)
	{
		isCasting = false;
		SetState(SKILL1);
	}
}

void ProtectionWarrior::OnHit(Collider* collider)
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

void ProtectionWarrior::EndATK()
{
	SetState(IDLE1);
}

void ProtectionWarrior::EndJUMP()
{
	SetState(IDLE1);
	isJump = false;
}

void ProtectionWarrior::EndIDLE()
{
	int idleChange = Random(1, 4);

	if (idleChange == 1)
	{
		SetState(IDLE1);
	}
	else if (idleChange == 2)
	{
		SetState(IDLE2);
	}
	else if (idleChange == 3)
	{
		SetState(IDLE3);
	}
}

void ProtectionWarrior::EndHit()
{
	if (cur_hp <= 0)
	{
		SetState(DIE);
	}
}

void ProtectionWarrior::EndDie()
{
	SetActive(false);
}

void ProtectionWarrior::EndCasting()
{
	SetState(IDLE1);
}