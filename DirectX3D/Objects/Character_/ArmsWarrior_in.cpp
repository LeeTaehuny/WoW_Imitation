#include "Framework.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/UI/PlayerUI_Bar.h"
#include "Objects/UI/PartyUI_Bar.h"

ArmsWarrior_in::ArmsWarrior_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	: CH_Base_ver2(type, ProfessionType::ArmsWarrior)
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

	// NPC / PC 구분
	switch (creatureType)
	{
	case CreatureType::Player:
		range = new SphereCollider(10);
		break;

	case CreatureType::NonPlayer:
		range = new SphereCollider(20);
		attackRange = new SphereCollider(2);
		attackRange->SetParent(this);

		skillList.push_back(new A_001_MortalStrike());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new A_002_Overpower());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new A_004_DiebytheSword());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new A_007_ColossusSmash());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new A_010_Bladestorm());
		skillList[skillList.size() - 1]->SetOwner(this);

		weapon = new Weapon("sword_1", WeaponType::Sword);
		weapon->SetParent(mainHand);
		break;
	}
	range->SetParent(this);

	FOR(totalEvents.size())
	{
		eventIters[i] = totalEvents[i].begin();
	}
	this->SetActive(true);

	// Status
	stat.maxHp = 1500.0f;
	stat.hp = stat.maxHp;
	stat.maxMp = 500;
	stat.mp = stat.maxMp;
	stat.damage = 150.0f;
	stat.defence = 100;

	mainHandBoneIndex = 37;

	// 음원 등록
	Audio::Get()->Add("WarriorAttack", "Sounds/ArmsWarrior/attack.wav", false, false, true);
	Audio::Get()->Add("WarriorHit", "Sounds/ArmsWarrior/hit.wav", false, false, true);
	Audio::Get()->Add("WarriorDeath", "Sounds/ArmsWarrior/death.wav", false, false, true);
}

ArmsWarrior_in::~ArmsWarrior_in()
{
	delete instancing;
	delete motion;
	delete myCollider;
	delete range;
	delete attackRange;
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

	// 공격 음원 재생
	if (isPlayAttackSound && !isRun)
	{
		attackSoundDelay += DELTA;
		if (attackSoundDelay >= 0.3f)
		{
			attackSoundDelay = 0.0f;
			// 음원 재생
			Audio::Get()->Play("WarriorAttack", Pos(), 1.0f);

			// 재생했다고 표시
			isRun = true;
		}
	}
	// 만약 재생했으면서, 사운드 재생이 끝난 상황이라면? 
	if (isRun && !Audio::Get()->IsPlaySound("WarriorAttack"))
	{
		// 변수 초기화
		isRun = false;
		isPlayAttackSound = false;
	}

	FOR(skillList.size())
		skillList[i]->Update();

	ExecuteEvent();
	CH_Base_ver2::Update();
	Transform::UpdateWorld();
}

void ArmsWarrior_in::Render()
{
	// ��Ƽ�� ���°� �ƴ϶�� ������Ʈ���� ����
	if (!Active()) return;

	FOR(skillList.size())
		skillList[i]->Render();

	if (attackRange)
		attackRange->Render();

	myCollider->Render();
	range->Render();
	CH_Base_ver2::Render();
}

void ArmsWarrior_in::GUIRender()
{
	if (ImGui::TreeNode((tag + "_DataBase").c_str()))
	{
		Transform::GUIRender();

		string Mtag = "M_" + to_string(index);
		//ImGui::SliderFloat((tag + "_HP").c_str(), &stat.hp, 0, stat.maxHp);
		//ImGui::SliderFloat((tag + "_MP").c_str(), (float*)&stat.mp, 0, stat.maxHp);
		ImGui::Text((Mtag + "_HP : " + to_string((int)stat.hp)).c_str());
		ImGui::Text((Mtag + "_MP : " + to_string(stat.mp)).c_str());

		ImGui::TreePop();
	}
}

void ArmsWarrior_in::EquipWeapon(Weapon* weapon)
{
	if (weapon == nullptr) return;

	this->weapon = weapon;
	weapon->SetOwner(this);
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
	if (curState == HIT || curState == DIE) return;

	if (atkGannnnn)
	{
		if (attackRange->IsCollision(saveMonsterCollider))
		{
			atkGannnnn = false;
		}
		else
		{
			if (!monsterSelectData->GetCollider()->Active())
			{
				monsterSelectData = nullptr;
				saveMonsterCollider = nullptr;
				atkGannnnn = false;
				return;
			}

			Vector3 velo = (monsterSelectData->GetTransform()->GlobalPos() - this->Pos()).GetNormalized();
			randomVelocity = velo;

			this->Pos() += velo * moveSpeed * DELTA;
			this->Rot().y = atan2(velo.x, velo.z) + XM_PI;

			attackRange->UpdateWorld();
			SetState(WALK_F);
		}
	}
	else if (!atkTarget)
	{
		AI_animation_Moving();
	}
	// 공격할 타겟이 있다면
	else
	{
		if (curState == ATTACK1 || curState == ATTACK2) return;

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

void ArmsWarrior_in::OnHit(float damage, bool motion)
{
	// 방어력 버프 존재 시
	if (isDefence)
	{
		float def = ((stat.defence * 1.3f) / (stat.defence + 100)) * 100;

		stat.hp -= (damage - damage * def);
	}
	else
	{
		float def = stat.defence / (stat.defence + 100) * 100;

		stat.hp -= (damage - damage * def);
	}


	if (stat.hp > 0)
	{
		if (!motion)
			SetState(HIT);

		Audio::Get()->Play("WarriorHit", Pos(), 1.0f);
	}
	else if (stat.hp <= 0)
	{
		
		stat.hp = 0.0f;
		SetState(DIE);		
		myCollider->SetActive(false);

		if (!one_die && Active())
		{
			one_die = true;
			Audio::Get()->Play("WarriorDeath", Pos(), 1.0f);
		}
	}

	if (creatureType == CreatureType::Player)
		playerUI->SetHpPercent(stat.hp / stat.maxHp);
	else
		CH->GetPartyUI()->SetHpPercent(stat.hp / stat.maxHp, stoi(GetTag().c_str()));
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

	if (randomVelocity == Vector3())
	{
		SetState(IDLE1);
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
	// 공격, 사망, 피격 중이라면 리턴
	if (curState == ATTACK1 || curState == DIE || curState == HIT) return;

	bool isMoveZ = false;
	bool isMoveX = false;

	// 이동 : W(앞), S(뒤), Q(좌), E(우)
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

	// 우클릭 중 좌우 이동 가능
	{
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
			// 엎, 뒤 이동 중에 방향 회전
			if (KEY_PRESS('W') || KEY_PRESS('S'))
			{
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

	// 이동량 체크 및 정규화
	if (velocity.Length() > 1) velocity.Normalize();
	if (!isMoveZ) velocity.z = Lerp(velocity.z, 0, deceleration * DELTA);
	if (!isMoveX) velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

	Matrix rotY = XMMatrixRotationY(Rot().y);
	Vector3 direction = XMVector3TransformCoord(velocity, rotY);

	// 해당 방향으로 이동
	this->Pos() += direction * -1 * moveSpeed * DELTA;

	// 점프 상태라면 모션 변경 X
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
	if (!isJump)
	{
		jumpVelocity -= 1.8f * gravityMult * DELTA;
		Pos().y += jumpVelocity;

		if (Pos().y < curheight)
		{
			Pos().y = curheight;
			jumpVelocity = 0;
		}
		return;
	}

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
	// 점프, 사망, 피격, 공격 모션 중에는 다시 공격 X
	if (curState == JUMP || curState == DIE || curState == HIT || curState == ATTACK1) return;

	// 인벤토리가 열려있으면 공격 X
	if (creatureType == CreatureType::Player && inventory->Active()) return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		// 무기가 존재한다면
		if (weapon)
		{
			SetState(ATTACK1);

			// 무기의 충돌체 정보를 키고 데미지를 전달하기
			weapon->GetCollider()->SetActive(true);
			weapon->SetDamage(stat.damage);

			// 음원 재생 설정
			isPlayAttackSound = true;
		}
	}
}

void ArmsWarrior_in::ai_attack()
{
	if (monsterSelectData == nullptr)
	{
		monsterSelectData = MONSTER->hitCollision(range);

		if (!monsterSelectData)
			return;

		saveMonsterCollider = monsterSelectData->GetCollider();
	}
	else if (!monsterSelectData->GetTransform()->Active())
	{
		monsterSelectData = nullptr;
		saveMonsterCollider = nullptr;
		return;
	}

	attackRange->UpdateWorld();
	if (!monsterSelectData->GetCollider()->Active()) return;

	// 공격할 대상을 바라보게 하는 코드
	Vector3 poldirect = monsterSelectData->GetTransform()->GlobalPos() - this->GlobalPos();
	this->Rot().y = atan2(poldirect.x, poldirect.z) + XM_PI;

	if (impact == 0)
	{
		impact++;
		imsiSkillStart = Random(1, 6);
	}

	switch (imsiSkillStart)
	{
	case 1:
		attackRange->Scale() = Vector3(1, 1, 1);
		attackRange->UpdateWorld();

		if (attackRange->IsCollision(saveMonsterCollider))
		{
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[0]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					c->UseSkill();
					impact = 0;
					return;
				}
				imsiSkillStart = 0;
				ActionTickTime = -1;
			}
		}
		else
		{
			atkGannnnn = true;
		}
		break;

	case 2:
		attackRange->Scale() = Vector3(1, 1, 1);
		attackRange->UpdateWorld();

		if (attackRange->IsCollision(saveMonsterCollider))
		{
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[1]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					c->UseSkill();
					impact = 0;
					return;
				}
				imsiSkillStart = 0;
				ActionTickTime = -1;
			}
		}
		else
		{
			atkGannnnn = true;
		}
		break;

	case 3:

		if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[2]))
		{
			if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
			{
				c->UseSkill();
				impact = 0;
				return;
			}
			imsiSkillStart = 0;
			ActionTickTime = -1;
		}
		break;

	case 4:
		attackRange->Scale() = Vector3(7, 7, 7);
		attackRange->UpdateWorld();

		if (attackRange->IsCollision(saveMonsterCollider))
		{
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[3]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					c->UseSkill(monsterSelectData);
					impact = 0;
					return;
				}
				imsiSkillStart = 0;
				ActionTickTime = -1;
			}
		}
		else
		{
			atkGannnnn = true;
		}
		break;

	case 5:
		attackRange->Scale() = Vector3(2, 2, 2);
		attackRange->UpdateWorld();

		if (attackRange->IsCollision(saveMonsterCollider))
		{
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[4]))
			{
				if (!c->GetIsCooldown() && c->GetrequiredMp() <= this->stat.mp)
				{
					c->UseSkill();
					impact = 0;
					return;
				}
				imsiSkillStart = 0;
				ActionTickTime = -1;
			}
		}
		else
		{
			atkGannnnn = true;
		}
		break;

	case 0:
		attackRange->Scale() = Vector3(1, 1, 1);
		attackRange->UpdateWorld();

		if (attackRange->IsCollision(saveMonsterCollider))
		{
			SetState(ATTACK1);
			// 무기가 존재하는 경우
			if (weapon)
			{
				// 무기의 콜라이더를 켜주고, 플레이어의 데미지를 전달
				weapon->GetCollider()->SetActive(true);
				weapon->SetDamage(stat.damage);

				// 음원 재생 설정
				isPlayAttackSound = true;
			}
			impact = 0;
			atkGannnnn = true;
		}
		else
		{
			impact = 0;
			atkGannnnn = true;
			return;
		}

		break;
	}
}

void ArmsWarrior_in::SetState(State state)
{
	if (state == curState) return;

	// 플레이어가 걷기로 상태를 변환했다면
	if (creatureType == CreatureType::Player && (state == WALK_F || state == WALK_B || state == WALK_L || state == WALK_R))
	{
		// 걷기 사운드 재생 중이 아니라면
		if (!Audio::Get()->IsPlaySound("Walk"))
		{
			Audio::Get()->Play("Walk", Pos(), 1.0f);
		}
	}
	else
	{
		// 걷기 사운드 재생중이라면
		if (Audio::Get()->IsPlaySound("Walk"))
		{
			Audio::Get()->Stop("Walk");
		}
	}

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
	SetState(IDLE1);
}

void ArmsWarrior_in::EndDie()
{
	one_die = false;
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