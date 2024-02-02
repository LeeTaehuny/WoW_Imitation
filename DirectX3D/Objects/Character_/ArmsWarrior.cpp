#include "Framework.h"

ArmsWarrior::ArmsWarrior() : CH_Base("ArmsWarrior")
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

void ArmsWarrior::Moving()
{
	// ����, ���� ���϶� �������� ����
	if (isJump) return;
	if (INTstate == (int)ATTACK1) return;
	if (INTstate == (int)ATTACK2) return;
	if (INTstate == (int)DIE) return;

	bool isMoveZ = false;
	bool isMoveX = false;
	float deceleration = 10;

	// ĳ���� �յ��¿� �̵��Դϴ�
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

	// ���콺 ��Ŭ���� 
	if (KEY_PRESS(VK_RBUTTON))
	{
		// �¿� �̵�
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
	// ���콺 ��Ŭ���� �ƴҶ�
	else
	{
		// �յڷ� �̵� ���� �ƴ� ��
		if (KEY_PRESS('W') || KEY_PRESS('S'))
		{
			// �¿� ȸ��
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