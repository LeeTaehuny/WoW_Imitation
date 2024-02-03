#include "Framework.h"

#define UPDATE(k) if (k != nullptr) k->Update()
#define UPDATEWORLD(k) if (k != nullptr) k->UpdateWorld()
#define RENDER(k) if (k != nullptr) k->Render()
#define GUIRENDER(k) if (k != nullptr) k->GUIRender()

MonsterManager::MonsterManager()
{
	skeleton_body = new ModelAnimatorInstancing("Skeleton");
	skeleton_body->ReadClip("Idle");
	skeleton_body->ReadClip("Attack_1");
	skeleton_body->ReadClip("Attack_2");
	skeleton_body->ReadClip("Walking_F");
	skeleton_body->ReadClip("Running");
	skeleton_body->ReadClip("Death");
	skeleton_body->ReadClip("Hit");
	skeleton_body->ReadClip("Scream");
}

MonsterManager::~MonsterManager()
{
	delete skeleton_body;

	for (Skeleton* skel : skeleton)
		delete skel;
	for (Collider* col : targets)
		delete col;
}

void MonsterManager::Update()
{
	skeleton_body->Update();

	for (Skeleton* skel : skeleton)
		UPDATE(skel);
}

void MonsterManager::Render()
{
	skeleton_body->Render();

	for (Skeleton* skel : skeleton)
		RENDER(skel);
}

void MonsterManager::SetTarget(Collider* transform)
{
	targets.push_back(transform);
}

void MonsterManager::SpawnSkeleton(Vector3 pos)
{
	int curindex = 0;
	if (skeleton.size() == 0){}
	else
	{
		for (UINT i = 0; i < skeleton.size(); ++i)
		{
			if (skeleton[i]->GetmyNumber() == curindex)
			{
				curindex++;
				continue;
			}
			else if (skeleton[i]->GetmyNumber() != curindex) break;
		}
	}	

	Transform* transform = skeleton_body->Add();
	transform->Scale() *= 0.01f;
	Skeleton* skel = new Skeleton(transform, skeleton_body, curindex, targets);
	skeleton.push_back(skel);
	skeleton[skeleton.size() - 1]->Spawn(pos);
}

void MonsterManager::HitCollider(Collider* collider)
{
	//Ray ray = CAM->ScreenPointToRay(mousePos);
	//
	//for (int i = 0; i < skeleton.size(); i++)
	//{
	//	if (skeleton[i]->GetCollider()->IsRayCollision())
	//	{
	//		skeleton[i]->SetState(Skeleton::HIT);
	//		skeleton[i]->targetHate[i] += 1;
	//	}
	//}
}