#include "Framework.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Skills/FireMage_Skill/F_000_Basic_Atttack.h"
#include "Objects/Skills/FireMage_Skill/F_001_Pyroblast.h"
#include "Objects/Skills/FireMage_Skill/F_002_FireBlast.h"
#include "Objects/Skills/FireMage_Skill/F_004_Scorch.h"
#include "Objects/Skills/FireMage_Skill/F_005_PhoenixFlame.h"
#include "Objects/Skills/FireMage_Skill/F_009_Combustion.h"
#include "Objects/Skills/FireMage_Skill/F_010_Meteor.h"
#include "Objects/Inventory/Inventory.h"

FireMage_in::FireMage_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	: CH_Base_ver2(type, ProfessionType::FireMage)
{
	transform->SetParent(this);
	this->instancing = instancing;
	this->index = index;

	transform->Scale() *= 0.01f;

	myCollider = new CapsuleCollider(0.5f, 1.0f);
	myCollider->SetParent(this);
	myCollider->Pos() = Vector3(0, 1.0f, 0);

	motion = instancing->GetMotion(index);
	totalEvents.resize(instancing->GetClipSize());
	eventIters.resize(instancing->GetClipSize());

	SetEvent(ATTACK1, bind(&FireMage_in::EndATK, this), 0.7f);
	SetEvent(DIE, bind(&FireMage_in::EndHit, this), 0.9f);
	SetEvent(JUMP, bind(&FireMage_in::EndHit, this), 0.9f);

	skillList.push_back(new F_000_Basic_Atttack());
	skillList[skillList.size() - 1]->SetOwner(this);
	// �ڽ��� Ÿ�Կ� ���� 
	switch (creatureType)
	{
	case CreatureType::Player:
		range = new SphereCollider(10);
		break;

	case CreatureType::NonPlayer:
		range = new SphereCollider(20);

		skillList.push_back(new F_001_Pyroblast());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new F_002_FireBlast());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new F_004_Scorch());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new F_005_PhoenixFlame());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new F_009_Combustion());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new F_010_Meteor());
		skillList[skillList.size() - 1]->SetOwner(this);
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
		// ���� �Ǻ��� bool ���� ����
		// 0 = �Ϲݰ���
		// 1 = �ҵ��� �۷�
		// 2 = ȭ�� �۷�
		// 3 = ���¿��
		// 4 = �һ����� �ұ�
		// 5 = ��ȭ
		// 6 = ���׿�
		attackSignal.push_back(false);
	}

	weapon = new Weapon("staff_3", WeaponType::Staff);
	weapon->Scale() *= 100;
	weapon->SetParent(mainHand);
}

FireMage_in::~FireMage_in()
{
	delete instancing;
	delete motion;
	delete myCollider;
	delete range;
}

void FireMage_in::Update()
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

	FOR(skillList.size())
		skillList[i]->Update();

	ExecuteEvent();
	CH_Base_ver2::Update();
	Transform::UpdateWorld();
}

void FireMage_in::Render()
{
	// ��Ƽ�� ���°� �ƴ϶�� ������Ʈ���� ����
	if (!Active()) return;

	myCollider->Render();
	range->Render();

	FOR(skillList.size())
		skillList[i]->Render();

	CH_Base_ver2::Render();
}

void FireMage_in::GUIRender()
{
	if (ImGui::TreeNode((tag + "_DataBase").c_str()))
	{
		Transform::GUIRender();

		string Mtag = "F_" + to_string(index);
		//ImGui::SliderFloat((tag + "_HP").c_str(), &stat.hp, 0, stat.maxHp);
		//ImGui::SliderFloat((tag + "_MP").c_str(), (float*)&stat.mp, 0, stat.maxHp);
		ImGui::Text((Mtag + "_HP : " + to_string((int)stat.hp)).c_str());
		ImGui::Text((Mtag + "_MP : " + to_string(stat.mp)).c_str());

		ImGui::TreePop();
	}
}

void FireMage_in::EquipWeapon(Weapon* weapon)
{
	if (weapon == nullptr) return;

	this->weapon = weapon;
	weapon->SetOwner(this);
	if (weapon->Scale() == Vector3(1, 1, 1))
		weapon->Scale() *= 100.0f; // 확인해보기
	weapon->Rot() = Vector3(0.0f, 11.0f, 0.0f);
	weapon->SetParent(mainHand);
}

void FireMage_in::PlayerUpdate()
{
	Control();
	//Casting();

	// �浹ü ������Ʈ
	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void FireMage_in::AIUpdate()
{
	if (!myPlayer) return;
	
	// ���� ������ Ÿ���� ���ٸ�
	if (!atkTarget)
	{
		AI_animation_Moving();
	}
	// ������ Ÿ���� �ִٸ�
	else
	{
		if (curState == ATTACK1 || curState == ATTACK2 || curState == ATTACK3) return;

		ActionTickTime -= DELTA;
		if (ActionTickTime <= 0)
		{
			ActionTickTime = Max_ActionTickTime;
			ai_attack();
		}

		if (!monsterSelectData)
		{
			AI_animation_Moving();
		}
	}

	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void FireMage_in::OnHit(float damage)
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

void FireMage_in::AI_animation_Moving()
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

	if (randomVelocity  == Vector3())
	{
		SetState(IDLE1);
	}
}

void FireMage_in::Control()
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

void FireMage_in::Moving()
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

void FireMage_in::Jump()
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

void FireMage_in::Attack()
{
	// ����, ���, �ǰ�, ���� ������ ��� ����
	if (curState == JUMP || curState == DIE || curState == HIT || curState == ATTACK1) return;

	if (attackSignal[0])
	{
		attackSignal[0] = false;

		// TODO : ���Ÿ� ���� �����
		skillList[0]->UseSkill(monsterSelectData);
	}
}

void FireMage_in::ai_attack()
{
	if (monsterSelectData == nullptr)
	{
		monsterSelectData = MONSTER->hitCollision(range);

		if (!monsterSelectData)
			return;
	}
	else if (!monsterSelectData->GetTransform()->Active())
	{
		monsterSelectData = nullptr;
		return;
	}

	// ������ ����� �ٶ󺸰� �ϴ� �ڵ�
	Vector3 poldirect = monsterSelectData->GetTransform()->GlobalPos() - this->GlobalPos();
	this->Rot().y = atan2(poldirect.x, poldirect.z) + XM_PI;

	if (!monsterSelectData->GetCollider()->Active()) return;
	int imsiSkillStart = Random(1, 7);
	switch (imsiSkillStart)
	{
	case 1:
		if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[1]))
		{
			if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
			{
				c->UseSkill(monsterSelectData);
				return;
			}
		}
		break;

	case 2:
		if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[2]))
		{
			if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
			{
				c->UseSkill(monsterSelectData);
				return;
			}
		}
		break;

	case 3:
		if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[3]))
		{
			if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
			{
				c->UseSkill(monsterSelectData);
				return;
			}
		}
		break;

	case 4:
		if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[4]))
		{
			if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
			{
				c->UseSkill(monsterSelectData);
				return;
			}
		}
		break;

	case 5:
		if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[5]))
		{
			if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
			{
				c->UseSkill();
				return;
			}
		}
		break;

	case 6:
		if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[6]))
		{
			if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
			{
				c->UseSkill(monsterSelectData);
				return;
			}
		}
		break;

	default:
		break;
	}

	skillList[0]->UseSkill(monsterSelectData);
}

void FireMage_in::SetState(State state)
{
	if (state == curState) return;
	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvents[state].begin();
}

void FireMage_in::EndATK()
{
	SetState(IDLE1);
}

void FireMage_in::EndHit()
{
	if (stat.hp <= 0)
	{
		SetState(DIE);
	}
}

void FireMage_in::EndDie()
{
	SetActive(false);
}

void FireMage_in::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void FireMage_in::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}