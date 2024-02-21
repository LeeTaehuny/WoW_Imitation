#include "Framework.h"

Skeleton_Knight::Skeleton_Knight(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<CH_Base_ver2*> target)
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
	SetEvent(ATTACK1, bind(&Skeleton_Knight::EndAttack, this), 0.7f);
	SetEvent(HIT, bind(&Skeleton_Knight::EndHit, this), 0.9f);
	SetEvent(DEATH, bind(&Skeleton_Knight::EndDeath, this), 1);

	Max_attack_deley = 1.5f;
	attack_deley = Max_attack_deley;

	FOR(totalEvents.size())
	{
		eventIters[i] = totalEvents[i].begin();
	}
	velocity = Vector3();

	// 플레이어 캐릭터의 수만큼 해이트 정보 확장
	targetHate.resize(this->target.size());
	attackBumwe = new BoxCollider(Vector3(100, 200, 200));
	attackBumwe->SetParent(this->transform);
	attackBumwe->Pos() = Vector3(0, 100, -150);
	attackBumwe->SetActive(false);

	hitText.resize(20);

	// 스켈레톤 나이트 스탯 설정
	maxHP = 2000.0f;
	curHP = maxHP;
	Atk = 300.0f;
}

Skeleton_Knight::~Skeleton_Knight()
{
	delete collider;
	delete attackRange;
	delete root;
	delete targetTransform;
	delete attackBumwe;
}

void Skeleton_Knight::Update()
{
	if (!transform->Active()) return;
	//if (curState == DEATH) return;
	//if (curState == SCREAM) return;
	//if (curState == HIT) return;

	Move();
	targetAttack();
	ExecuteEvent();
	//UpdateUI();

	root->SetWorld(instancing->GetTransformByNode(index, 3));
	collider->UpdateWorld();
	attackRange->UpdateWorld();
	attackBumwe->UpdateWorld();
}

void Skeleton_Knight::Render()
{
	collider->Render();
	attackRange->Render();
	attackBumwe->Render();
}

void Skeleton_Knight::PostRender()
{
	if (!transform->Active()) return;

	for (HitDesc& hit : hitText)
	{
		// 출력 Off면 출력 X
		if (!hit.isPrint) continue;

		// 지속시간 감소 및 출력 여부 체크
		hit.duration -= DELTA;

		if (hit.duration <= 0.0f)
		{
			hit.isPrint = false;
		}

		// 몬스터의 위치 구하기
		Vector3 screenPos = CAM->WorldToScreen(collider->GlobalPos());
		// 출력 (남은 시간에 비례해서 점점 올라가게 설정하기)
		Font::Get()->RenderText(hit.damage, { screenPos.x + 15.0f , screenPos.y - (50.0f * hit.duration) + 55.0f });
	}
}

void Skeleton_Knight::Hit(float amount, int targetNumber)
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

	for (int i = 0; i < hitText.size(); i++)
	{
		// 출력 off 상태이면
		if (!hitText[i].isPrint)
		{
			// 출력 설정하기
			hitText[i].isPrint = true;
			hitText[i].duration = 1.0f;
			hitText[i].damage = to_string((int)amount);

			break;
		}
	}
}

void Skeleton_Knight::Spawn(Vector3 pos)
{
	transform->SetActive(true);
	collider->SetActive(true);
	SetState(WALKING);
	curHP = maxHP;
	transform->Pos() = pos;
}

void Skeleton_Knight::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void Skeleton_Knight::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}

void Skeleton_Knight::EndAttack()
{
	attackBumwe->SetActive(false);
	SetState(WALKING);
}

void Skeleton_Knight::EndHit()
{
	SetState(WALKING);
}

void Skeleton_Knight::EndDeath()
{
	transform->SetActive(false);
	//collider->SetActive(false);
}

void Skeleton_Knight::SetState(State state)
{
	if (state == curState) return;
	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvents[state].begin();
}

void Skeleton_Knight::Move()
{
	if (!Moving) return;
	if (curState == DEATH) return;
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

void Skeleton_Knight::targetAttack()
{
	if (curState == ATTACK1 || curState == DEATH || curState == HIT) return;
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

	if (attackRange->IsCollision(targetTransform->GetCollider()) &&
		oneAttack == 0)
	{
		Moving = false;
		attackBumwe->SetActive(true);
		SetState(ATTACK1);
	}
	else if (oneAttack == 1 && curState != ATTACK1)
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

void Skeleton_Knight::UpdateUI()
{
}