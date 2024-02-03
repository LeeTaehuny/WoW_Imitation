#include "Framework.h"
#include "KimScene.h"

#define UPDATE(k) if (k != nullptr) k->Update()
#define UPDATEWORLD(k) if (k != nullptr) k->UpdateWorld()
#define RENDER(k) if (k != nullptr) k->Render()
#define GUIRENDER(k) if (k != nullptr) k->GUIRender()

#define MONSTER MonsterManager::Get()

KimScene::KimScene()
{
	//mainPlayer = new ProtectionWarrior();
	//skel = new ModelAnimator("Skeleton");
	//
	//skel->ReadClip("Attack_1");
	//skel->ReadClip("Attack_2");
	//skel->ReadClip("Death");
	//skel->ReadClip("Hit");
	//skel->ReadClip("Idle");
	//skel->ReadClip("Running");
	//skel->ReadClip("Scream");
	//skel->ReadClip("Walking_F");
	//
	//skel->PlayClip(3);
	MONSTER;

	coll.push_back(new BoxCollider());
	coll.push_back(new BoxCollider());
	coll.push_back(new BoxCollider());
	coll.push_back(new BoxCollider());

	int pop = 20;
	coll[0]->Pos() = Vector3(pop);
	coll[1]->Pos() = Vector3(-pop);
	coll[2]->Pos() = Vector3(0, 0, pop);
	coll[3]->Pos() = Vector3(0, 0, -pop);

	FOR(coll.size())
	{
		MONSTER->SetTarget(coll[i]);
	}
}

KimScene::~KimScene()
{
	delete mainPlayer;

	for (Collider* col : coll)
		delete col;
	delete skel;
}

void KimScene::Update()
{
	float forward = 3;

	if (KEY_DOWN('1')) dlatl = coll[0];
	if (KEY_DOWN('2')) dlatl = coll[1];
	if (KEY_DOWN('3')) dlatl = coll[2];
	if (KEY_DOWN('4')) dlatl = coll[3];

	if (KEY_DOWN(VK_LEFT))
	{
		MONSTER->SpawnSkeleton(Vector3());
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		MONSTER->SpawnSkeletonKnight(Vector3());
	}

	MONSTER->Update();
	UPDATE(mainPlayer);
	UPDATE(skel);

	for (Collider* col : coll)
		col->UpdateWorld();
}

void KimScene::PreRender()
{
}

void KimScene::Render()
{
	MONSTER->Render();

	RENDER(mainPlayer);
	RENDER(skel);

	for (Collider* col : coll)
		col->Render();
}

void KimScene::PostRender()
{
}

void KimScene::GUIRender()
{
	GUIRENDER(mainPlayer);
	GUIRENDER(skel);
	for (Collider* col : coll)
		col->GUIRender();
}
