#include "Framework.h"

VAlkier::VAlkier(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<CH_Base_ver2*> target)
{
	this->transform = transform;
	this->instancing = instancing;
	this->index = index;
	this->target = target;

	//transform->Scale() *= 0.03f;

	root = new Transform();

	collider = new CapsuleCollider(100, 100);
	collider->SetParent(this->transform);
	collider->Pos() = { 0.0f, 50.0f, 0.0f };
	attackRange = new SphereCollider(5);
	attackRange->SetParent(root);

	motion = instancing->GetMotion(index);
	totalEvents.resize(instancing->GetClipSize());
	eventIters.resize(instancing->GetClipSize());

	// 애니메이션 세팅
	//SetEvent(DEATH, bind(&VAlkier::EndDeath, this), 1);

	Max_attack_deley = 1.5f;
	attack_deley = Max_attack_deley;

	FOR(totalEvents.size())
	{
		eventIters[i] = totalEvents[i].begin();
	}
	velocity = Vector3();

	attackTarget_serch = new SphereCollider();
	attackTarget_serch->SetParent(this->transform);
	attackTarget_serch->Scale() *= 1200;

	tong = new SphereCollider(55);
	tong->UpdateWorld();

	// 현재 몬스터와 가장 가까운 캐릭터를 판별하기 위한 부분
	{
		attackTarget_serch->UpdateWorld();
		float atk_leng = FLT_MAX;
		vector<CH_Base_ver2*> characterData = CH->GetCharcterData();
		CH_Base_ver2* lom = target[0];
		for (int i = 0; i < characterData.size(); ++i)
		{
			if (attackTarget_serch->IsCollision(characterData[i]->GetCollider()))
			{
				Vector3 leng = characterData[i]->GlobalPos() - attackTarget_serch->GlobalPos();
				float min = leng.Length();

				if (atk_leng >= min)
				{
					atk_leng = min;
					lom = characterData[i];
				}
			}
		}
		targetTransform = lom;
	}
	hitText.resize(20);

	// 발키리 스탯 설정
	maxHP = 500.0f;
	curHP = maxHP;
	Atk = 0.0f;

	tong = new SphereCollider(53);
}

VAlkier::~VAlkier()
{
	delete collider;
	delete attackRange;
	delete root;
	delete targetTransform;
	delete attackBumwe;
	delete attackTarget_serch;
	delete tong;
}

void VAlkier::Update()
{
	if (!transform->Active()) return;
	if (curHP <= 0)
	{
		transform->SetActive(false);
		collider->SetActive(false);
		return;
	}

	if (!TaxiMode)
		Move();
	else
		targetAttack();

	if (!targetTransform) return;

	ExecuteEvent();
	MonsterBase::targetActiveSerch();
	//UpdateUI();

	if (curState == FLYING)
	{
		if (!Audio::Get()->IsPlaySound("valkyr_wing"))
		{
			Audio::Get()->Play("valkyr_wing");
		}
	}

	root->SetWorld(instancing->GetTransformByNode(index, 3));
	collider->UpdateWorld();
}

void VAlkier::Render()
{
	if (!transform->Active()) return;

	collider->Render();
	attackRange->Render();
	tong->Render();
}

void VAlkier::PostRender()
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

void VAlkier::Hit(float amount)
{
	curHP -= amount;

	if (curHP <= 0)
	{
		//SetState(DEATH);
		transform->SetActive(false);
		collider->SetActive(false);
		curHP = 0.0f;
		Audio::Get()->Play("valkyr_die");
	}
	else
	{
		Audio::Get()->Play("valkyr_hit");
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

void VAlkier::Spawn(Vector3 pos)
{
	transform->SetActive(true);
	collider->SetActive(true);
	SetState(FLYING);
	curHP = maxHP;
	transform->Pos() = pos;
}

void VAlkier::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void VAlkier::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}

void VAlkier::EndDeath()
{
	transform->SetActive(false);
}

void VAlkier::SetState(State state)
{
	if (state == curState) return;
	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvents[state].begin();
}

void VAlkier::Move()
{
	if (targetTransform == nullptr) return;

	velocity = (targetTransform->GlobalPos() - transform->GlobalPos()).GetNormalized();

	transform->Pos() += velocity * 5 * DELTA;
	transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;

	attackRange->UpdateWorld();
	if (attackRange->IsCollision(targetTransform->GetCollider()))
	{
		TaxiMode = true;
		return;
	}
}

void VAlkier::targetAttack()
{
	tong->UpdateWorld();
	if (tong->IsCollision(collider))
	{
		velocity = (transform->GlobalPos() - Vector3()).GetNormalized();

		transform->Pos() += velocity * 2.5f * DELTA;
		transform->Pos().y = 5;
		transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;

		Vector3 drive = transform->Pos();
		drive.y -= 1.5f;
		targetTransform->Pos() = drive;
		targetTransform->UpdateWorld();
	}
	else
	{
		targetTransform = nullptr;
		transform->SetActive(false);
		collider->SetActive(false);
	}	
}

void VAlkier::UpdateUI()
{
}