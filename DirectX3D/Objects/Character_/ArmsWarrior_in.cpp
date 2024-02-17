#include "Framework.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"

ArmsWarrior_in::ArmsWarrior_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
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

	SetEvent(ATTACK1, bind(&ArmsWarrior_in::EndATK, this), 0.7f);
	SetEvent(HIT, bind(&ArmsWarrior_in::EndHit, this), 0.9f);
	SetEvent(DIE, bind(&ArmsWarrior_in::EndDie, this), 1);

	// �ڽ��� Ÿ�Կ� ���� 
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

	mainHandBoneIndex = 37;
	weapon = new Weapon("sword_1", WeaponType::Sword);
	weapon->SetParent(mainHand);
}

ArmsWarrior_in::~ArmsWarrior_in()
{
	delete instancing;
	delete motion;
	delete myCollider;
	delete range;
}

void ArmsWarrior_in::Update()
{
	// ��Ƽ�� ���°� �ƴ϶�� ������Ʈ���� ����
	if (!Active()) return;

	// �÷��̾� Ÿ�Կ� ���� ������Ʈ ����
	switch (creatureType)
	{
	case CreatureType::Player:
		PlayerUpdate();
		break;

	case CreatureType::NonPlayer:
		AIUpdate();
		break;
	}

	ExecuteEvent();
	CH_Base_ver2::Update();
	Transform::UpdateWorld();
}

void ArmsWarrior_in::Render()
{
	// ��Ƽ�� ���°� �ƴ϶�� ������Ʈ���� ����
	if (!Active()) return;

	myCollider->Render();
	range->Render();
	CH_Base_ver2::Render();
}

void ArmsWarrior_in::GUIRender()
{
}

void ArmsWarrior_in::EquipWeapon(Weapon* weapon)
{
	if (weapon == nullptr) return;

	this->weapon = weapon;
	weapon->SetParent(mainHand);
}

void ArmsWarrior_in::AddHp(float value)
{
	if (value > 0)
	{
		// ü�� ȸ��
		stat.hp += value;

		// ���� �ִ� ü�·����� �������ٸ�?
		if (stat.hp > stat.maxHp)
		{
			// �ִ� ü�¾����� ����
			stat.hp = stat.maxHp;
		}
	}
	
}

void ArmsWarrior_in::PlayerUpdate()
{
	Control();
	//Casting();

	// �浹ü ������Ʈ
	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void ArmsWarrior_in::AIUpdate()
{
	if (!myPlayer) return;
	AI_animation_Moving();

	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void ArmsWarrior_in::OnHit(float damage)
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

void ArmsWarrior_in::AI_animation_Moving()
{
	// ���� �÷��̾��� ������ �ִٸ�
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
	// �÷��̾��� �ֺ��� �ƴ϶��
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

void ArmsWarrior_in::Control()
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

void ArmsWarrior_in::Moving()
{
	// ����, ����, ���� ��, �׾��� ��� �������� �ʱ�
	if (curState == ATTACK1 || curState == DIE || curState == HIT) return;

	bool isMoveZ = false;
	bool isMoveX = false;

	// ĳ���� �⺻ �̵� : W(��), S(��), Q(��), E(��)
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

	// ĳ���� ���콺 ��Ŭ���� ���� �̵� ��ȭ
	{
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
		else
		{
			// �յڷ� �̵� ���� �ƴ� ��
			if (KEY_PRESS('W') || KEY_PRESS('S'))
			{
				// �¿� ȸ��
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

	// ���ӵ� ����
	if (velocity.Length() > 1) velocity.Normalize();
	if (!isMoveZ) velocity.z = Lerp(velocity.z, 0, deceleration * DELTA);
	if (!isMoveX) velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY);

	// ��ġ �̵�
	this->Pos() += direction * -1 * moveSpeed * DELTA;

	// ������ ����� �ִϸ��̼� ���� X
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

void ArmsWarrior_in::Jump()
{
	// �������� �ƴ϶�� ����
	if (!isJump) return;

	jumpVelocity -= 1.8f * gravityMult * DELTA;
	Pos().y += jumpVelocity;

	// ������ ���� ���̺��� ��ġ�� ���ٸ�?
	if (Pos().y < curheight)
	{
		// ��ġ �ʱ�ȭ �� ���� ��ȯ
		Pos().y = curheight;
		jumpVelocity = 0;
		SetState(IDLE1);
		isJump = false;
	}
}

void ArmsWarrior_in::Attack()
{
	// ����, ���, �ǰ�, ���� ������ ��� ����
	if (curState == JUMP || curState == DIE || curState == HIT || curState == ATTACK1) return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		SetState(ATTACK1);

		// ���Ⱑ �����ϴ� ���
		if (weapon)
		{
			// ������ �ݶ��̴��� ���ְ�, �÷��̾��� �������� ����
			weapon->GetCollider()->SetActive(true);
			weapon->SetDamage(stat.damage);
		}
	}
}

void ArmsWarrior_in::SetState(State state)
{
	if (state == curState) return;
	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvents[state].begin();
}

void ArmsWarrior_in::EndATK()
{
	SetState(IDLE1);

	if (weapon)
	{
		// ������ �������Ƿ� ������ �浹ü ������ ���ֱ�
		weapon->GetCollider()->SetActive(false);
		weapon->ClearHit();
	}
}

void ArmsWarrior_in::EndHit()
{
	if (stat.hp <= 0)
	{
		SetState(DIE);
	}
}

void ArmsWarrior_in::EndDie()
{
	SetActive(false);
}

void ArmsWarrior_in::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void ArmsWarrior_in::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}