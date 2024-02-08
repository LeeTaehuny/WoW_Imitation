#include "Framework.h"
#include "KimScene.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Character_/CH_Base.h"
#include "Objects/Character_/MarksmanshipHunter.h"
#include "Objects/Character_/ArmsWarrior.h"
#include "Objects/Character_/HolyPriest.h"
#include "Objects/Character_/FireMage.h"
#include "Objects/Character_/ProtectionWarrior.h"

//#include "Objects/Character_ver2/CH_Base_ver2.h"
//#include "Objects/Character_ver2/ProtectionWarrior_in.h"

// #define UPDATE(k) if (k != nullptr) k->Update()
// #define UPDATEWORLD(k) if (k != nullptr) k->UpdateWorld()
// #define RENDER(k) if (k != nullptr) k->Render()
// #define GUIRENDER(k) if (k != nullptr) k->GUIRender()

KimScene::KimScene()
{
	pl = new ModelAnimatorInstancing("ProtectionWarrior");
	pl->ReadClip("Idle_1");
	pl->ReadClip("Attack_1");
	pl->ReadClip("Walk_F");
	pl->ReadClip("Walk_B");
	pl->ReadClip("Walk_L");
	pl->ReadClip("Walk_R");
	pl->ReadClip("Die");
	pl->ReadClip("Hit");
	pl->ReadClip("Jump");
	pl->ReadClip("S_Casting");

	pol = new ModelAnimatorInstancing("FireMage");
	pol->ReadClip("Idle_1");
	pol->ReadClip("Attack_1");
	pol->ReadClip("Walk_F");
	pol->ReadClip("Walk_B");
	pol->ReadClip("Walk_L");
	pol->ReadClip("Walk_R");


	pal = new ModelAnimatorInstancing("HolyPriest");
	pal->ReadClip("Idle_1");
	pal->ReadClip("Attack_1");
	pal->ReadClip("Walk_F");
	pal->ReadClip("Walk_B");
	pal->ReadClip("Walk_L");
	pal->ReadClip("Walk_R");

	Transform* transform = pl->Add();
	player = new ProtectionWarrior_in(CreatureType::Player, transform, pl, count);
	count++;
	CAM->SetTarget(player);
	//MONSTER->SetTarget(mainPlayer->GetCollider());

	spawn(pl);
	spawn(pl);
	spawn(pl);
	spawn(pol);
	spawn(pol);
	spawn(pol);
	spawn(pal);
	spawn(pal);
	spawn(pal);
	//MONSTER;

	//int pop = 20;
	//coll[0]->Pos() = Vector3(pop);
	//coll[1]->Pos() = Vector3(-pop);
	//coll[2]->Pos() = Vector3(0, 0, pop);
	//coll[3]->Pos() = Vector3(0, 0, -pop);

	//FOR(coll.size())
	//{
	//	MONSTER->SetTarget(coll[i]);
	//}

	//MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	//MONSTER->SpawnScarecrow(Vector3(10));
	//MONSTER->SpawnScarecrow(Vector3(-10));
}

KimScene::~KimScene()
{
	//delete mainPlayer;
	delete pl;
	delete pol;
	delete pal;
	delete player;

	for (ProtectionWarrior_in* ch : NPC)
		delete ch;
}

void KimScene::Update()
{
	//if (KEY_DOWN(VK_LEFT))
	//{
	//	MONSTER->SpawnSkeleton(Vector3());
	//}
	//if (KEY_DOWN(VK_RIGHT))
	//{
	//	MONSTER->SpawnSkeletonKnight(Vector3());
	//}

	//if (KEY_DOWN('P'))
	//{
	//	spawn();
	//}

	pl->Update();
	pol->Update();
	pal->Update();
	player->Update();
	for (ProtectionWarrior_in* ch : NPC)
		if (ch != nullptr) ch->Update();
}

void KimScene::PreRender()
{

}

void KimScene::Render()
{
	pl->Render();
	pol->Render();
	pal->Render();
	player->Render();
	for (ProtectionWarrior_in* ch : NPC)
		if (ch != nullptr) ch->Render();
}

void KimScene::PostRender()
{
	player->UIRender();
}

void KimScene::GUIRender()
{
	
}

void KimScene::spawn(ModelAnimatorInstancing* pol)
{
	Transform* transform1 = pol->Add();
	ProtectionWarrior_in* ppp = new ProtectionWarrior_in(CreatureType::NonPlayer, transform1, pol, 0);
	ppp->SetPlayer(player);
	NPC.push_back(ppp);
	count++;
}
