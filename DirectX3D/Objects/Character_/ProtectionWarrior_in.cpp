﻿#include "Framework.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/UI/PlayerUI_Bar.h"
#include "Objects/UI/PartyUI_Bar.h"

ProtectionWarrior_in::ProtectionWarrior_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
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

	SetEvent(ATTACK1, bind(&ProtectionWarrior_in::EndATK, this), 0.7f);
	SetEvent(HIT, bind(&ProtectionWarrior_in::EndHit, this), 0.9f);
	SetEvent(DIE, bind(&ProtectionWarrior_in::EndDie, this), 1);
	SetEvent(SKILL1, bind(&ProtectionWarrior_in::EndCasting, this), 1);

	// 자신의 타입에 따라 
	switch (creatureType)
	{
	case CreatureType::Player:
		range = new SphereCollider(10);

		Audio::Get()->Add("PW_01_impack", "Sounds/ProtectionWarrior/skill/P_001_impact.ogg", false, false, true);
		Audio::Get()->Add("PW_01_swing", "Sounds/ProtectionWarrior/skill/P_001_swing.ogg", false, false, true);
		Audio::Get()->Add("PW_02_using", "Sounds/ProtectionWarrior/skill/P_002_impact.ogg", false, false, true);
		Audio::Get()->Add("PW_09_using", "Sounds/ProtectionWarrior/skill/P_009_using.ogg", false, false, true);
		break;

	case CreatureType::NonPlayer:
		range = new SphereCollider(20);
		attackRange = new SphereCollider(2);
		attackRange->SetParent(this);

		skillList.push_back(new P_001_Avengers_Shield());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new P_002_HOTR());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new P_009_Eye_Of_Tyr());
		skillList[skillList.size() - 1]->SetOwner(this);

		weapon = new Weapon("hammer_1", WeaponType::Hammer);
		weapon->SetParent(mainHand);

		break;
	}
	range->SetParent(this);

	sub = new Transform();
	sub->SetParent(this);

	shield = new Weapon("shield", WeaponType::Shield);
	shield->Rot().y = XM_PI / 2;
	shield->SetParent(sub);

	FOR(totalEvents.size())
	{
		eventIters[i] = totalEvents[i].begin();
	}
	this->SetActive(true);

	mainHandBoneIndex = 37;

	// Status
	stat.maxHp = 2000.0f;
	stat.hp = stat.maxHp;
	stat.maxMp = 500;
	stat.mp = stat.maxMp;
	stat.damage = 100.0f;
	stat.defence = 100;

	Audio::Get()->Add("PW_atk", "Sounds/ProtectionWarrior/attack.ogg", false, false, true);
	Audio::Get()->Add("PW_die", "Sounds/ProtectionWarrior/die.ogg", false, false, true);
	Audio::Get()->Add("PW_hit", "Sounds/ProtectionWarrior/hit.ogg", false, false, true);
}

ProtectionWarrior_in::~ProtectionWarrior_in()
{
	delete instancing;
	delete motion;
	delete myCollider;
	delete range;
	delete attackRange;
}

void ProtectionWarrior_in::Update()
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

	// 실드 업데이트
	if (shield && sub)
	{
		sub->SetWorld(instancing->GetTransformByNode(index, 18));
		sub->GlobalPos() = GlobalPos();

		shield->Update();
	}

	FOR(skillList.size())
		skillList[i]->Update();

	ExecuteEvent();
	CH_Base_ver2::Update();
	Transform::UpdateWorld();
}

void ProtectionWarrior_in::Render()
{
	// 액티브 상태가 아니라면 업데이트하지 않음
	if (!Active()) return;

	if (attackRange)
		attackRange->Render();

	FOR(skillList.size())
		skillList[i]->Render();

	if (shield)
	{
		shield->Render();
	}

	myCollider->Render();
	range->Render();
	CH_Base_ver2::Render();
}

void ProtectionWarrior_in::GUIRender()
{
	if (ImGui::TreeNode((tag + "_DataBase").c_str()))
	{
		Transform::GUIRender();

		string Mtag = "P_" + to_string(index);
		ImGui::Text((Mtag + "_HP : " + to_string((int)stat.hp)).c_str());
		ImGui::Text((Mtag + "_MP : " + to_string(stat.mp)).c_str());

		ImGui::TreePop();
	}
}

void ProtectionWarrior_in::EquipWeapon(Weapon* weapon)
{
	if (weapon == nullptr) return;

	this->weapon = weapon;
	weapon->SetOwner(this);

	weapon->SetParent(mainHand);
}

void ProtectionWarrior_in::PlayerUpdate()
{
	Control();

	if (one_atk_sound)
	{
		one_atk_time -= DELTA;
		if (one_atk_time <= 0)
		{
			one_atk_time = Max_one_atk_time;
			Audio::Get()->Play("PW_atk", Pos(), 1.0f);
			one_atk_sound = false;
		}
	}

	// 충돌체 업데이트
	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void ProtectionWarrior_in::AIUpdate()
{
	if (!myPlayer) return;
	if (curState == HIT || curState == DIE) return;

	if (one_atk_sound02)
	{
		one_atk_time -= DELTA;
		if (one_atk_time <= 0)
		{
			one_atk_time = Max_one_atk_time;
			Audio::Get()->Play("PW_atk", Pos(), 1.0f);
			one_atk_sound02 = false;
		}
	}

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
			this->Pos().y = curheight;
			this->Rot().y = atan2(velo.x, velo.z) + XM_PI;

			attackRange->UpdateWorld();
			SetState(WALK_F);
		}
	}
	// 지금 공격할 타겟이 없다면
	else if (!atkTarget)
	{
		AI_animation_Moving();
	}
	// 공격할 타겟이 있다면
	else
	{
		if (curState == ATTACK1 || curState == SKILL1) return;

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

void ProtectionWarrior_in::OnHit(float damage, bool motion)
{
	float def = stat.defence / (stat.defence + 100) * 100;

	stat.hp -= (damage - damage * def);

	if (stat.hp > 0)
	{
		if (!motion)
			SetState(HIT);

		Audio::Get()->Play("PW_hit", Pos(), 1.0f);
	}
	else if (stat.hp <= 0)
	{
		stat.hp = 0.0f;
		SetState(DIE);
		myCollider->SetActive(false);

		if (!one_die && Active())
		{
			one_die = true;
			Audio::Get()->Play("PW_die", Pos(), 1.0f);
		}
	}

	if (creatureType == CreatureType::Player)
		playerUI->SetHpPercent(stat.hp / stat.maxHp);
	else
		CH->GetPartyUI()->SetHpPercent(stat.hp / stat.maxHp, stoi(GetTag().c_str()));
}

void ProtectionWarrior_in::AI_animation_Moving()
{
	// 내가 플레이어의 주위에 있다면
	if (myPlayer->GetRange()->IsCollision(myCollider))
	{
		randomHangdong -= DELTA;
		if (randomHangdong <= 0)
		{
			randomHangdong = MAX_randomHangdong;
			randomVelocity = Vector3(Random(-1, 2), 0, Random(-1, 2));
		}

		this->Pos() += randomVelocity * (moveSpeed / 10) * DELTA;
		this->Pos().y = curheight;
		this->Rot().y = atan2(randomVelocity.x, randomVelocity.z) + XM_PI;

		SetState(WALK_F);
	}
	// 플레이어의 주변이 아니라면
	else
	{
		Vector3 velo = (myPlayer->Pos() - this->Pos()).GetNormalized();
		randomVelocity = velo;
		randomHangdong = 2.0f;

		this->Rot().y = atan2(velo.x, velo.z) + XM_PI;

		this->Pos() += velo * moveSpeed * DELTA;
		this->Pos().y = curheight;
		SetState(WALK_F);
	}

	if (randomVelocity == Vector3())
	{
		SetState(IDLE1);
	}
}

void ProtectionWarrior_in::Control()
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

void ProtectionWarrior_in::Moving()
{
	// 점프, 공격, 맞을 때, 죽었을 경우 움직이지 않기
	if (curState == ATTACK1 || curState == DIE || curState == HIT || curState == SKILL1) return;

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
	this->Pos() += direction * -1 * moveSpeed * DELTA;

	// 점프인 경우라면 애니메이션 설정 X
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

void ProtectionWarrior_in::Jump()
{
	// 점프중이 아니라면 리턴
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

	// 현재의 지정 높이보다 위치가 낮다면?
	if (Pos().y < curheight)
	{
		// 위치 초기화 및 상태 전환
		Pos().y = curheight;
		jumpVelocity = 0;
		SetState(IDLE1);
		isJump = false;
	}
}

void ProtectionWarrior_in::Attack()
{
	// 점프, 사망, 피격, 공격 상태인 경우 리턴
	if (curState == JUMP || curState == DIE || curState == HIT || curState == ATTACK1) return;

	// 인벤토리가 열려있으면 공격 X
	if (creatureType == CreatureType::Player && inventory->Active()) return;

	if (KEY_DOWN(VK_LBUTTON) && weapon != nullptr)
	{
		SetState(ATTACK1);

		one_atk_sound = true;
		weapon->GetCollider()->SetActive(true);
		weapon->SetDamage(stat.damage);
	}
}

void ProtectionWarrior_in::ai_attack()
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
		imsiSkillStart = Random(1, 4);
	}

	switch (imsiSkillStart)
	{
	case 1:
		attackRange->Scale() = Vector3(5, 5, 5);
		attackRange->UpdateWorld();

		if (attackRange->IsCollision(saveMonsterCollider))
		{
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[0]))
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

	case 2:
		attackRange->Scale() = Vector3(1, 1, 1);
		attackRange->UpdateWorld();

		if (attackRange->IsCollision(saveMonsterCollider))
		{
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skillList[1]))
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

	case 3:
		attackRange->Scale() = Vector3(5, 5, 5);
		attackRange->UpdateWorld();

		if (attackRange->IsCollision(saveMonsterCollider))
		{
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
			
			// 무기의 콜라이더를 켜주고, 플레이어의 데미지를 전달
			weapon->GetCollider()->SetActive(true);
			weapon->SetDamage(stat.damage);
			
			impact = 0;
			atkGannnnn = true;
			one_atk_sound02 = true;
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

void ProtectionWarrior_in::SetState(State state)
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

void ProtectionWarrior_in::EndATK()
{
	SetState(IDLE1);

	if (weapon)
	{
		// 공격이 끝났으므로 무기의 충돌체 정보를 꺼주기
		weapon->GetCollider()->SetActive(false);
		weapon->ClearHit();
	}
}

void ProtectionWarrior_in::EndHit()
{
	SetState(IDLE1);
}

void ProtectionWarrior_in::EndDie()
{
	one_die = false;
	SetActive(false);
}

void ProtectionWarrior_in::EndCasting()
{
	SetState(IDLE1);
}

void ProtectionWarrior_in::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void ProtectionWarrior_in::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}