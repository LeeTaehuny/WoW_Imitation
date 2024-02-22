#include "Framework.h"

Scarecrow::Scarecrow(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<CH_Base_ver2*> target)
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

	motion = instancing->GetMotion(index);
	totalEvents.resize(instancing->GetClipSize());
	eventIters.resize(instancing->GetClipSize());

	// 애니메이션 세팅
	SetEvent(HIT, bind(&Scarecrow::EndHit, this), 0.9f);

	FOR(totalEvents.size())
	{
		eventIters[i] = totalEvents[i].begin();
	}
	velocity = Vector3();

	SetState(IDLE);

	hitText.resize(20);

	// 허수아비 스탯 설정
	maxHP = 10000.0f;
	curHP = maxHP;
	Atk = 100.0f;
}

Scarecrow::~Scarecrow()
{
	delete collider;
	delete attackRange;
	delete root;
	delete targetTransform;
	delete attackBumwe;
}

void Scarecrow::Update()
{
	if (!transform->Active()) return;

	if (curHP <= 0)
	{
		curHP = maxHP;
	}

	ExecuteEvent();

	root->SetWorld(instancing->GetTransformByNode(index, 3));
	collider->UpdateWorld();
}

void Scarecrow::Render()
{
	collider->Render();
}

void Scarecrow::PostRender()
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

void Scarecrow::Hit(float amount)
{
	SetState(HIT);

	curHP -= amount;

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

void Scarecrow::Spawn(Vector3 pos)
{
	transform->SetActive(true);
	collider->SetActive(true);
	curHP = maxHP;
	transform->Pos() = pos;
}

void Scarecrow::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0) return;
	totalEvents[clip][timeRatio] = event;
}

void Scarecrow::ExecuteEvent()
{
	int index = curState;

	if (totalEvents[index].empty()) return;
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration;

	if (eventIters[index]->first > ratio) return;

	eventIters[index]->second();
	eventIters[index]++;
}

void Scarecrow::EndHit()
{
	SetState(IDLE);
}

void Scarecrow::SetState(State state)
{
	if (state == curState) return;
	curState = state;
	instancing->PlayClip(index, state);
	eventIters[state] = totalEvents[state].begin();
}