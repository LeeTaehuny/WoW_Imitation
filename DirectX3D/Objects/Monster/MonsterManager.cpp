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

	skeletonKnight_body = new ModelAnimatorInstancing("Skeleton_Knight");
	skeletonKnight_body->ReadClip("Idle");
	skeletonKnight_body->ReadClip("Attack_1");
	skeletonKnight_body->ReadClip("Walking");
	skeletonKnight_body->ReadClip("Death");
	skeletonKnight_body->ReadClip("Hit");

	scarecrow_body = new ModelAnimatorInstancing("Skeleton_Knight");
	scarecrow_body->ReadClip("Idle");
	scarecrow_body->ReadClip("Hit");
}

MonsterManager::~MonsterManager()
{
	delete skeleton_body;
	delete skeletonKnight_body;
	delete scarecrow_body;

	for (Skeleton* skel : skeleton)
		delete skel;
	for (Skeleton_Knight* skel : skeleton_Knight)
		delete skel;
	for (Scarecrow* skel : scarecrow)
		delete skel;

	for (Collider* col : targets)
		delete col;
	for (Collider* col : monsterCollider)
		delete col;
}

void MonsterManager::Update()
{
	skeleton_body->Update();
	skeletonKnight_body->Update();
	scarecrow_body->Update();

	for (Skeleton* skel : skeleton)
		UPDATE(skel);
	for (Skeleton_Knight* skel : skeleton_Knight)
		UPDATE(skel);
	for (Scarecrow* skel : scarecrow)
		UPDATE(skel);
}

void MonsterManager::Render()
{
	skeleton_body->Render();
	skeletonKnight_body->Render();
	scarecrow_body->Render();

	for (Skeleton* skel : skeleton)
		RENDER(skel);
	for (Skeleton_Knight* skel : skeleton_Knight)
		RENDER(skel);
	for (Scarecrow* skel : scarecrow)
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
	monsterCollider.push_back(skel->collider);
	skeleton.push_back(skel);
	skeleton[skeleton.size() - 1]->Spawn(pos);
}
void MonsterManager::SpawnSkeletonKnight(Vector3 pos)
{
	int curindex = 0;
	if (skeleton_Knight.size() == 0) {}
	else
	{
		for (UINT i = 0; i < skeleton_Knight.size(); ++i)
		{
			if (skeleton_Knight[i]->GetmyNumber() == curindex)
			{
				curindex++;
				continue;
			}
			else if (skeleton_Knight[i]->GetmyNumber() != curindex) break;
		}
	}

	Transform* transform = skeletonKnight_body->Add();
	transform->Scale() *= 0.02f;
	Skeleton_Knight* skel = new Skeleton_Knight(transform, skeletonKnight_body, curindex, targets);
	monsterCollider.push_back(skel->collider);
	skeleton_Knight.push_back(skel);
	skeleton_Knight[skeleton_Knight.size() - 1]->Spawn(pos);
}
void MonsterManager::SpawnScarecrow(Vector3 pos)
{
	int curindex = 0;
	if (scarecrow.size() == 0) {}
	else
	{
		for (UINT i = 0; i < scarecrow.size(); ++i)
		{
			if (scarecrow[i]->GetmyNumber() == curindex)
			{
				curindex++;
				continue;
			}
			else if (scarecrow[i]->GetmyNumber() != curindex) break;
		}
	}

	Transform* transform = scarecrow_body->Add();
	transform->Scale() *= 0.02f;
	Scarecrow* skel = new Scarecrow(transform, scarecrow_body, curindex, targets);
	monsterCollider.push_back(skel->collider);
	scarecrow.push_back(skel);
	scarecrow[scarecrow.size() - 1]->Spawn(pos);
}