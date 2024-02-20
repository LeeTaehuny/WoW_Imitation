#include "Framework.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/UI/PlayerUI_Bar.h"

HolyPriest_in::HolyPriest_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	: CH_Base_ver2(type, ProfessionType::HolyPriest)
{
	transform->SetParent(this);
	this->instancing = instancing;
	this->index = index;

	//this->Scale() *= 0.01;
	//this->Scale() *= 100;

	myCollider = new CapsuleCollider(0.5f, 1.0f);
	myCollider->SetParent(this);
	myCollider->Pos() = Vector3(0, 1.0f, 0);

	motion = instancing->GetMotion(index);
	totalEvents.resize(instancing->GetClipSize());
	eventIters.resize(instancing->GetClipSize());

	SetEvent(ATTACK1, bind(&HolyPriest_in::EndATK, this), 0.7f);
	SetEvent(HIT, bind(&HolyPriest_in::EndHit, this), 0.9f);
	SetEvent(DIE, bind(&HolyPriest_in::EndDie, this), 1);

	FOR(totalEvents.size())
	{
		eventIters[i] = totalEvents[i].begin();
	}
	this->SetActive(true);

	mainHandBoneIndex = 37;


	skillList.push_back(new H_000_Basic_Atttack());
	skillList[skillList.size() - 1]->SetOwner(this);
	// �ڽ��� Ÿ�Կ� ���� 
	switch (creatureType)
	{
	case CreatureType::Player:
		range = new SphereCollider(10);
		break;

	case CreatureType::NonPlayer:
		range = new SphereCollider(20);

		skillRange = new SphereCollider(5);
		skillRange->SetParent(this);

		skillList.push_back(new H_001_Holy_Word_Serenity());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new H_002_Holy_Word_Sanctify());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new H_003_Guardian_Spirit());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new H_004_Holy_Word_Chastise());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new H_006_Circle_Of_Healing());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new H_008_Divine_Hymn());
		skillList[skillList.size() - 1]->SetOwner(this);
		break;
	}
	range->SetParent(this);

	FOR(skillList.size())
	{
		// ���� �Ǻ��� bool ���� ����
		// 0 = �Ϲݰ���
		// 1 = ���� �Ǵ� : ���
		// 2 = ���� �Ǵ� : �ż�ȭ
		// 3 = ��ȣ ��ȥ
		// 4 = ���� �Ǵ� : ��¡
		// 5 = ġ���� ������
		// 6 = õ���� ����
		attackSignal.push_back(false);
	}
	weapon = new Weapon("staff_2", WeaponType::Staff);
	weapon->SetParent(mainHand);
}

HolyPriest_in::~HolyPriest_in()
{
	delete instancing;
	delete motion;
	delete myCollider;
	delete range;
	delete skillRange;

	for (SkillBase* skill : skillList)
		delete skill;
}

void HolyPriest_in::Update()
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

void HolyPriest_in::Render()
{
	// ��Ƽ�� ���°� �ƴ϶�� ������Ʈ���� ����
	if (!Active()) return;

	myCollider->Render();
	range->Render();

	FOR(skillList.size())
		skillList[i]->Render();

	if (creatureType == CreatureType::NonPlayer)
	{
		skillRange->Render();
	}

	CH_Base_ver2::Render();
}

void HolyPriest_in::GUIRender()
{
	if (ImGui::TreeNode((tag + "_DataBase").c_str()))
	{
		Transform::GUIRender();

		string Mtag = "H_" + to_string(index);
		ImGui::Text((Mtag + "_HP : " + to_string((int)stat.hp)).c_str());
		ImGui::Text((Mtag + "_MP : " + to_string(stat.mp)).c_str());

		ImGui::TreePop();
	}
}

void HolyPriest_in::EquipWeapon(Weapon* weapon)
{
	if (weapon == nullptr) return;

	this->weapon = weapon;
	weapon->SetOwner(this);
	weapon->SetParent(mainHand);
}

void HolyPriest_in::PlayerUpdate()
{
	Control();
	//Casting();

	// �浹ü ������Ʈ
	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void HolyPriest_in::AIUpdate()
{
	if (!myPlayer) return;

	if (use002skill)
	{
		if (skillRange->IsCollision(characterSelectData->GetCollider()))
		{
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[2]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					use002skill = false;
					c->UseSkill();
					return;
				}
			}
		}
		else
		{
			Vector3 velo = (characterSelectData->GlobalPos() - this->Pos()).GetNormalized();
			this->Pos() += velo * moveSpeed * DELTA;
			this->Rot().y = atan2(velo.x, velo.z) + XM_PI;
			skillRange->UpdateWorld();
			SetState(WALK_F);
		}
	}
	else if (use008skill)
	{
		if (skillRange->IsCollision(characterSelectData->GetCollider()))
		{
			pressSkill -= DELTA;
			if (pressSkill <= 0)
			{
				pressSkill = Max_pressSkill;
				ActionTickTime = Max_ActionTickTime;
				if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[6]))
				{
					if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
					{
						c->UseSkill();
						use008skill = false;
						return;
					}
				}
			}
		}
		else
		{
			Vector3 velo = (characterSelectData->GlobalPos() - this->Pos()).GetNormalized();
			this->Pos() += velo * moveSpeed * DELTA;
			this->Rot().y = atan2(velo.x, velo.z) + XM_PI;
			skillRange->UpdateWorld();
			SetState(WALK_F);
		}
	}
	// ���� ������ Ÿ���� ���ٸ�
	else if (!atkTarget)
	{
		AI_animation_Moving();
	}
	// ������ Ÿ���� �ִٸ�
	else
	{
		ActionTickTime -= DELTA;
		if (ActionTickTime <= 0)
		{
			ActionTickTime = Max_ActionTickTime;
			if (characterSelectData == nullptr)
			{
				float min_Hpvalue = 0.60f;
				vector<CH_Base_ver2*> characters = CH->GetCharcterData();
				for (int i = 0; i < characters.size(); i++)
				{
					if (range->IsCollision(characters[i]->GetCollider()))
					{
						if (this == characters[i]) continue;

						float cur_hpValue = characters[i]->GetStat().hp / characters[i]->GetStat().maxHp;
						if (min_Hpvalue >= cur_hpValue)
						{
							min_Hpvalue = cur_hpValue;
							characterSelectData = characters[i];
						}
					}
				}
			}
			else if (!characterSelectData->Active())
			{
				characterSelectData = nullptr;
				return;
			}

			if (characterSelectData)
			{
				// ȸ�� ��� ĳ������ ü�� ���� ���ϱ�
				target_Proportion = characterSelectData->GetStat().hp / characterSelectData->GetStat().maxHp;
				if (target_Proportion <= 0.6)
				{
					heal = true;
					atk = false;
				}
				else
				{
					characterSelectData = nullptr;
					heal = false;
					atk = true;
				}				
			}
			else
			{
				heal = false;
				atk = true;
			}

			ai_attack();
		}

		if (!heal && !atk)
		{
			AI_animation_Moving();
		}
	}

	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void HolyPriest_in::OnHit(float damage)
{
	stat.hp -= damage;

	if (stat.hp > 0)
	{
		SetState(HIT);
	}
	else if (stat.hp <= 0)
	{
		stat.hp = 0.0f;
		SetState(DIE);
	}

	playerUI->SetHpPercent(stat.hp / stat.maxHp);
}

void HolyPriest_in::AI_animation_Moving()
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

	if (randomVelocity == Vector3())
	{
		SetState(IDLE1);
	}
}

void HolyPriest_in::Control()
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

void HolyPriest_in::Moving()
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

void HolyPriest_in::Jump()
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

void HolyPriest_in::Attack()
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

void HolyPriest_in::ai_attack()
{
	// ����, ���, �ǰ�, ���� ������ ��� ����
	if (curState == DIE || curState == HIT || curState == ATTACK1) return;

	if (heal)
	{
		Vector3 poldirect = characterSelectData->GlobalPos() - this->GlobalPos();
		this->Rot().y = atan2(poldirect.x, poldirect.z) + XM_PI;

		int imsiSkillStart = Random(1, 6);
		switch (imsiSkillStart)
		{
		case 1:
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[1]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					c->UseSkill(characterSelectData);
					return;
				}
			}
			break;
		case 2:
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[2]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					use002skill = true;
					return;
				}
			}
			break;
		case 3:
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[3]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					c->UseSkill(characterSelectData);
					return;
				}
			}
			break;
		case 4:
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[5]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					c->UseSkill(characterSelectData);
					return;
				}
			}
			break;
		case 5:
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[6]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					c->UseSkill();
					use008skill = true;
					return;
				}
			}
			break;
		default:
			break;
		}

		if (monsterSelectData == nullptr)
		{
			monsterSelectData = MONSTER->hitCollision(range);

			if (!monsterSelectData)
			{
				heal = false;
				atk = false;
				return;
			}
		}
		else if (!monsterSelectData->GetCollider()->Active())
		{
			monsterSelectData = nullptr;
			heal = false;
			atk = false;
			return;
		}
		poldirect = monsterSelectData->GetCollider()->GlobalPos() - this->GlobalPos();
		this->Rot().y = atan2(poldirect.x, poldirect.z) + XM_PI;

		skillList[0]->UseSkill(monsterSelectData);
	}
	else if (atk)
	{
		if (monsterSelectData == nullptr)
		{
			monsterSelectData = MONSTER->hitCollision(range);

			if (!monsterSelectData)
			{
				heal = false;
				atk = false;
				return;
			}
		}
		else if (!monsterSelectData->GetCollider()->Active())
		{
			monsterSelectData = nullptr;
			heal = false;
			atk = false;
			return;
		}

		// ������ ����� �ٶ󺸰� �ϴ� �ڵ�
		Vector3 poldirect = monsterSelectData->GetCollider()->GlobalPos() - this->GlobalPos();
		this->Rot().y = atan2(poldirect.x, poldirect.z) + XM_PI;

		if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[4]))
		{
			if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
			{
				c->UseSkill(monsterSelectData);
				return;
			}
		}

		skillList[0]->UseSkill(monsterSelectData);
	}
}

void HolyPriest_in::SetState(State state)
{
	if (state == curState) return;
	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvents[state].begin();
}

void HolyPriest_in::EndATK()
{
	SetState(IDLE1);
}

void HolyPriest_in::EndHit()
{
	if (stat.hp <= 0)
	{
		SetState(DIE);
	}
	else
	{
		SetState(IDLE1);
	}
}

void HolyPriest_in::EndDie()
{
	SetActive(false);
}

void HolyPriest_in::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void HolyPriest_in::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}