#include "Framework.h"

Scarecrow::Scarecrow(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<Collider*> target)
{
	this->transform = transform;
	this->instancing = instancing;
	this->index = index;
	this->target = target;

	root = new Transform();

	collider = new CapsuleCollider(30, 100);
	collider->SetParent(root);
	collider->Pos() = { -15.0f, 10.0f, 0.0f };

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
	//if (curState == DEATH) return;
	//if (curState == SCREAM) return;
	//if (curState == HIT) return;

	//if (KEY_DOWN('1')) targetNumber = 0;
	//if (KEY_DOWN('2')) targetNumber = 1;
	//if (KEY_DOWN('3')) targetNumber = 2;
	//if (KEY_DOWN('4')) targetNumber = 3;

	ExecuteEvent();
	//UpdateUI();
	//Hit(1, targetNumber);

	root->SetWorld(instancing->GetTransformByNode(index, 3));
	collider->UpdateWorld();
}

void Scarecrow::Render()
{
	collider->Render();
	//attackRange->Render();
	//attackBumwe->Render();
}

void Scarecrow::PostRender()
{
}

void Scarecrow::Hit(float amount, int targetNumber)
{
	//targetHate[targetNumber] += amount;

	SetState(HIT);

	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	Ray ray = CAM->ScreenPointToRay(mousePos);
	//	if (collider->IsRayCollision(ray, nullptr))
	//	{
	//		SetState(HIT);
	//	}
	//}
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