﻿#include "Framework.h"

Skeleton::Skeleton(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<CH_Base_ver2*> target)
{
	this->transform = transform;
	this->instancing = instancing;
	this->index = index;
	this->target = target;

	root = new Transform();

	collider = new CapsuleCollider(30, 100);
	collider->Scale().y *= 1.5f;
	collider->Scale().x *= 2.5f;
	collider->Scale().z *= 2.5f;
	collider->SetParent(this->transform);
	collider->Pos() = { 0.0f, 110.0f, 0.0f };
	attackRange = new SphereCollider(200);
	attackRange->SetParent(root);

	motion = instancing->GetMotion(index);
	totalEvents.resize(instancing->GetClipSize());
	eventIters.resize(instancing->GetClipSize());

	// 애니메이션 세팅
	SetEvent(ATTACK1, bind(&Skeleton::EndAttack, this), 0.7f);
	SetEvent(ATTACK2, bind(&Skeleton::EndAttack, this), 0.7f);
	SetEvent(HIT, bind(&Skeleton::EndHit, this), 0.9f);
	SetEvent(DEATH, bind(&Skeleton::EndDeath, this), 1);

	Max_attack_deley = 1.5f;
	attack_deley = Max_attack_deley;

	FOR(totalEvents.size())
	{
		eventIters[i] = totalEvents[i].begin();
	}
	velocity = Vector3();

	// 플레이어 캐릭터의 수만큼 해이트 정보 확장
	targetHate.resize(this->target.size());
	attackBumwe = new BoxCollider(Vector3(200, 200, 200));
	attackBumwe->SetParent(this->transform);
	attackBumwe->Pos() = Vector3(0, 100, -150);
	attackBumwe->SetActive(false);
}

Skeleton::~Skeleton()
{
	delete collider;
	delete attackRange;
	delete root;
	delete targetTransform;
	delete attackBumwe;
}

void Skeleton::Update()
{
	if (!transform->Active()) return;
	//if (curState == DEATH) return;
	//if (curState == SCREAM) return;
	//if (curState == HIT) return;

	//if (KEY_DOWN('1')) targetNumber = 0;
	//if (KEY_DOWN('2')) targetNumber = 1;
	//if (KEY_DOWN('3')) targetNumber = 2;
	//if (KEY_DOWN('4')) targetNumber = 3;

	Move();
	targetAttack();
	ExecuteEvent();
	//UpdateUI();
	//Hit(1, targetNumber);

	root->SetWorld(instancing->GetTransformByNode(index, 3));
	collider->UpdateWorld();
	attackRange->UpdateWorld();
	attackBumwe->UpdateWorld();
}

void Skeleton::Render()
{
	collider->Render();
	attackRange->Render();
	attackBumwe->Render();
}

void Skeleton::PostRender()
{
}

void Skeleton::Hit(float amount, int targetNumber)
{
	targetHate[targetNumber] += amount;

	curHP -= amount;

	if (curHP <= 0)
	{
		SetState(DEATH);
		collider->SetActive(false);
		curHP = 0.0f;
	}
	else
	{
		SetState(HIT);
	}

	/*if (KEY_DOWN(VK_LBUTTON))
	{
		Ray ray = CAM->ScreenPointToRay(mousePos);
		if (collider->IsRayCollision(ray, nullptr))
		{
			targetHate[targetNumber] += amount;

			if (curHP <= 0)
			{
				SetState(DEATH);
			}
			else
			{
				SetState(HIT);
			}
		}
	}*/
	
	//curHP = curHP - amount;
	//hpBar->SetAmount(curHP / maxHP);	
}

void Skeleton::Spawn(Vector3 pos)
{
	transform->SetActive(true);
	collider->SetActive(true);
	SetState(RUN);
	curHP = maxHP;
	transform->Pos() = pos;
}

void Skeleton::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void Skeleton::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}

void Skeleton::EndAttack()
{
	attackBumwe->SetActive(false);
	SetState(RUN);
}

void Skeleton::EndHit()
{
	SetState(RUN);
}

void Skeleton::EndDeath()
{
	transform->SetActive(false);
	//collider->SetActive(false);
}

void Skeleton::SetState(State state)
{
	if (state == curState) return;
	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvents[state].begin();
}

void Skeleton::Move()
{
	if (!Moving) return;
	if (curState == DEATH) return;
	if (curState == SCREAM) return;
	if (curState == HIT) return;

	float Maxhate = 0;
	int targetNumver = 0;
	for (int i = 0; i < targetHate.size(); i++)
	{
		if (Maxhate <= targetHate[i])
		{
			Maxhate = targetHate[i];
			targetNumver = i;
			targetTransform = target[i];
		}
	}

	velocity = (target[targetNumver]->GlobalPos() - transform->GlobalPos()).GetNormalized();

	transform->Pos() += velocity * 2 * DELTA;
	transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
}

void Skeleton::targetAttack()
{
	if (curState == DEATH) return;
	if (curState == SCREAM) return;
	if (curState == HIT) return;

	if (attackBumwe->Active())
	{
		attack_deley -= DELTA;
		if (attack_deley <= 0)
		{
			attack_deley = Max_attack_deley;
			if (attackBumwe->IsCollision(targetTransform->GetCollider()))
			{
				if (oneAttack == 0)
				{
					targetTransform->OnHit(Atk);
					attackBumwe->SetActive(false);
					oneAttack++;
				}
			}
		}
	}
	else
	{
		attack_deley = Max_attack_deley;
	}

	if (curState == ATTACK1 || curState == ATTACK2) return;
	if (attackRange->IsCollision(targetTransform->GetCollider()) &&
		oneAttack == 0)
	{
		Moving = false;
		attackBumwe->SetActive(true);
		int ron = Random(1, 3);
		if (ron == 1)
		{
			SetState(ATTACK1);
			Max_attack_deley = 0.9f;
			attack_deley = Max_attack_deley;
		}
		else if (ron == 2)
		{
			SetState(ATTACK2);
			Max_attack_deley = 1.5f;
			attack_deley = Max_attack_deley;
		}
	}
	else if (oneAttack == 1 && curState == RUN)
	{
		oneAttack = 0;
		Moving = true;
		attackBumwe->SetActive(false);
	}
	else
	{
		Moving = true;
		attackBumwe->SetActive(false);
	}
}

void Skeleton::UpdateUI()
{
}