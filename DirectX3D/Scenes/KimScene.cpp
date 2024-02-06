#include "Framework.h"
#include "KimScene.h"

#define UPDATE(k) if (k != nullptr) k->Update()
#define UPDATEWORLD(k) if (k != nullptr) k->UpdateWorld()
#define RENDER(k) if (k != nullptr) k->Render()
#define GUIRENDER(k) if (k != nullptr) k->GUIRender()



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

	skill = new P_001_Avengers_Shield();

	MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	MONSTER->SpawnScarecrow(Vector3(10));
	MONSTER->SpawnScarecrow(Vector3(-10));
}

KimScene::~KimScene()
{
	delete mainPlayer;

	for (Collider* col : coll)
		delete col;
	delete skel;
	delete skill;
	delete par;
	delete particleSystem;
}

void KimScene::Update()
{
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

	if (KEY_DOWN(VK_SPACE))
		skill->UseSkill(CAM->Pos());

	if (KEY_DOWN(VK_LBUTTON))
	{
		for (Collider* coll : MONSTER->monsterCollider)
		{
			Ray ray = CAM->ScreenPointToRay(mousePos);

			if (coll->IsRayCollision(ray, nullptr))
			{
				if (P_001_Avengers_Shield* t = dynamic_cast<P_001_Avengers_Shield*>(skill))
					t->SetEnemy(coll);
				break;
			}
		}
	}
	skill->Update();

	//if (KEY_DOWN('A'))
	//	particleSystem->Play(Vector3());

	MONSTER->Update();
	UPDATE(mainPlayer);
	UPDATE(skel);
	UPDATE(particleSystem);

	UPDATE(par);

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

	skill->Render();
	RENDER(par);
	RENDER(particleSystem);
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