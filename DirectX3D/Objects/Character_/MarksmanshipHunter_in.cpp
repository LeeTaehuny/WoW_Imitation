#include "Framework.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/UI/PlayerUI_Bar.h"
#include "Objects/UI/PartyUI_Bar.h"

MarksmanshipHunter_in::MarksmanshipHunter_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
	: CH_Base_ver2(type, ProfessionType::MarksmanshipHunter)
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

	SetEvent(ATTACK1, bind(&MarksmanshipHunter_in::EndATK, this), 0.7f);
	SetEvent(HIT, bind(&MarksmanshipHunter_in::EndHit, this), 0.9f);
	SetEvent(DIE, bind(&MarksmanshipHunter_in::EndDie, this), 1);

	skillList.push_back(new M_000_Basic_Atttack());
	skillList[skillList.size() - 1]->SetOwner(this);
	switch (creatureType)
	{
	case CreatureType::Player:
		range = new SphereCollider(20);

		Audio::Get()->Add("MH_01_impact","Sounds/MarksmanshipHunter/skill/M_001_impact.ogg", false, false, true);
		Audio::Get()->Add("MH_03_using", "Sounds/MarksmanshipHunter/skill/M_003_using.ogg", false, false, true);
		Audio::Get()->Add("MH_05_using", "Sounds/MarksmanshipHunter/skill/M_005_using.ogg", false, false, true);
		Audio::Get()->Add("MH_08_using", "Sounds/MarksmanshipHunter/skill/M_008_using.ogg", false, false, true);
		Audio::Get()->Add("MH_09_using", "Sounds/MarksmanshipHunter/skill/M_009_using.ogg", false, false, true);
		Audio::Get()->Add("MH_10_using", "Sounds/MarksmanshipHunter/skill/M_010_using.ogg", false, false, true);
		break;

	case CreatureType::NonPlayer:
		range = new SphereCollider(15);

		skillList.push_back(new M_001_Aimed_Shot());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new M_003_Rapid_Fire());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new M_005_Chimaera_Shot());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new M_008_Multi_Shot());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new M_009_Volley());
		skillList[skillList.size() - 1]->SetOwner(this);

		skillList.push_back(new M_010_Wailing_Arrow());
		skillList[skillList.size() - 1]->SetOwner(this);

		weapon = new Weapon("bow_1", WeaponType::Staff);
		weapon->SetParent(mainHand);
		break;
	}

	range->SetParent(this);

	FOR(totalEvents.size())
	{
		eventIters[i] = totalEvents[i].begin();
	}
	this->SetActive(true);

	mainHandBoneIndex = 23;

	// Status
	stat.maxHp = 700.0f;
	stat.hp = stat.maxHp;
	stat.maxMp = 700;
	stat.mp = stat.maxMp;
	stat.damage = 150.0f;
	stat.defence = 100;

	Audio::Get()->Add("MH_atk", "Sounds/MarksmanshipHunter/attack.ogg", false, false, true);
	Audio::Get()->Add("MH_die", "Sounds/MarksmanshipHunter/die.ogg", false, false, true);
	Audio::Get()->Add("MH_hit", "Sounds/MarksmanshipHunter/hit.ogg", false, false, true);
}

MarksmanshipHunter_in::~MarksmanshipHunter_in()
{
	delete instancing;
	delete motion;
	delete myCollider;
	delete range;

	for (SkillBase* skill : skillList)
		delete skill;
}

void MarksmanshipHunter_in::Update()
{
	// 액티브가 꺼져 있다면 함수 종료
	if (!Active()) return;

	// 캐릭터의 타입에따라 업데이트를 다르게 함
	// NPC와 플레이어 구분
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

void MarksmanshipHunter_in::Render()
{
	// 액티브가 꺼져 있다면 함수 종료
	if (!Active()) return;

	myCollider->Render();
	range->Render();

	FOR(skillList.size())
		skillList[i]->Render();

	CH_Base_ver2::Render();
}

void MarksmanshipHunter_in::GUIRender()
{
	if (ImGui::TreeNode((tag + "_DataBase").c_str()))
	{
		Transform::GUIRender();

		string Mtag = "M_" + to_string(index);
		ImGui::Text((Mtag + "_HP : " + to_string((int)stat.hp)).c_str());
		ImGui::Text((Mtag + "_MP : " + to_string(stat.mp)).c_str());

		ImGui::TreePop();
	}
}

void MarksmanshipHunter_in::EquipWeapon(Weapon* weapon)
{
	if (weapon == nullptr) return;

	this->weapon = weapon;
	weapon->SetOwner(this);
	weapon->Rot() = Vector3(0.0f, 21.0f, 20.0f);
	weapon->SetParent(mainHand);
}

void MarksmanshipHunter_in::PlayerUpdate()
{
	Control();

	if (one_atk_sound)
	{
		one_atk_time -= DELTA;
		if (one_atk_time <= 0)
		{
			one_atk_time = Max_one_atk_time;
			Audio::Get()->Play("MH_atk", Pos(), 1.0f);
			one_atk_sound = false;
		}
	}

	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void MarksmanshipHunter_in::AIUpdate()
{
	if (!myPlayer) return;
	if (curState == HIT || curState == DIE) return;

	if (one_atk_sound02)
	{
		one_atk_time -= DELTA;
		if (one_atk_time <= 0)
		{
			one_atk_time = Max_one_atk_time;
			Audio::Get()->Play("MH_atk", Pos(), 1.0f);
			one_atk_sound02 = false;
		}
	}

	// 공격 명령이 활성화되었을 경우
	if (!atkTarget)
	{
		AI_animation_Moving();
	}
	// 공격 명령이 비활성화인 경우
	else
	{
		ai_attack();
	}

	myCollider->UpdateWorld();
	range->UpdateWorld();
}

void MarksmanshipHunter_in::OnHit(float damage, bool motion)
{
	float def = stat.defence / (stat.defence + 100) * 100;

	stat.hp -= (damage - damage * def);

	if (stat.hp > 0)
	{
		if (!motion)
			SetState(HIT);
		Audio::Get()->Play("MH_hit", Pos(), 1.0f);

	}
	else if (stat.hp <= 0)
	{
		stat.hp = 0.0f;
		SetState(DIE);
		myCollider->SetActive(false);

		if (!one_die && Active())
		{
			one_die = true;
			Audio::Get()->Play("MH_die", Pos(), 1.0f);
		}
	}

	if (creatureType == CreatureType::Player)
		playerUI->SetHpPercent(stat.hp / stat.maxHp);
	else
		CH->GetPartyUI()->SetHpPercent(stat.hp / stat.maxHp, stoi(GetTag().c_str()));
}

void MarksmanshipHunter_in::AI_animation_Moving()
{
	// 플레이어의 범위에 머물러 있는 경우 작동하는 이프문
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
	// 플레이어의 범위안에 없는 경우 작동하는 이프문
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

void MarksmanshipHunter_in::Control()
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

void MarksmanshipHunter_in::Moving()
{
	/* 공격, 죽음, 히트, 캐스팅 애니메이션이 실행중이라면 함수 종료 */
	if (curState == ATTACK1 || curState == DIE || curState == HIT ||
		curState == SKILL1 || curState == SKILL2) return;

	bool isMoveZ = false;
	bool isMoveX = false;

	/* 캐릭터 기본 이동 : W(앞), S(뒤), Q(좌), E(우) */
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

	/* 캐릭터 마우스 우클릭에 따른 이동 변화 */
	{
		if (KEY_PRESS(VK_RBUTTON))
		{
			/* 좌우 이동 */
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
			/* 앞뒤로 이동 중이 아닐 때 */
			if (KEY_PRESS('W') || KEY_PRESS('S'))
			{
				/* 좌우 회전 */
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

void MarksmanshipHunter_in::Jump()
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

void MarksmanshipHunter_in::Attack()
{
	// 점프, 죽음, 히트, 공격 애니메이션이 실행중이라면 함수를 작동시키지 않음
	if (curState == JUMP || curState == DIE || curState == HIT || curState == ATTACK1) return;
	if (!weapon) return;

	// 무기가 착용되어 있고 타겟이 널이 아닌 경우 공격 가능
	if (KEY_DOWN(VK_LBUTTON) && weapon != nullptr && targetMonster)
	{
		skillList[0]->UseSkill(targetMonster);
		one_atk_sound = true;
	}
}

void MarksmanshipHunter_in::ai_attack()
{
	// 죽음, 히트, 공격 애니메이션이 재생중이라면 함수 종료
	if (curState == DIE || curState == HIT || curState == ATTACK1) return;

	ActionTickTime -= DELTA;
	if (ActionTickTime <= 0)
	{
		ActionTickTime = Max_ActionTickTime;
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

		// 스킬을 사용할때 대상을 포게하기 위함
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
					c->UseSkill(monsterSelectData);
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

		one_atk_sound02 = true;
		skillList[0]->UseSkill(monsterSelectData);
	}

	if (!monsterSelectData)
	{
		AI_animation_Moving();
	}
}

void MarksmanshipHunter_in::SetState(State state)
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

void MarksmanshipHunter_in::EndATK()
{
	SetState(IDLE1);
}

void MarksmanshipHunter_in::EndHit()
{
	SetState(IDLE1);
}

void MarksmanshipHunter_in::EndDie()
{
	one_die = false;
	SetActive(false);
}

void MarksmanshipHunter_in::EndCasting()
{
	SetState(IDLE1);
}

void MarksmanshipHunter_in::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void MarksmanshipHunter_in::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}