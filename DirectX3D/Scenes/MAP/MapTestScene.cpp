#include "Framework.h"
#include "MapTestScene.h"

MapTestScene::MapTestScene()
{
	bossmap = new BossMap();
	//bossmap->Rot().y += 1.575f;
	//bossmap->Pos().y = -100.0f;
	
	//Test = new SphereCollider(2);
	//Test->Pos().y += 7.0f;
	//Test->Pos().x += 40;
	//bossmap->Scale() *= 10;

	instaning = new ModelAnimatorInstancing("ProtectionWarrior");
	instaning->ReadClip("Idle_1");
	instaning->ReadClip("Attack_1");
	instaning->ReadClip("Walk_F");
	instaning->ReadClip("Walk_B");
	instaning->ReadClip("Walk_L");
	instaning->ReadClip("Walk_R");
	instaning->ReadClip("Die");
	instaning->ReadClip("Hit");
	instaning->ReadClip("Jump");
	instaning->ReadClip("S_Casting");

	Transform* transform = instaning->Add();
	player = new ProtectionWarrior_in(CreatureType::Player, transform, instaning, 0);
	//PLAYER->Pos() = bossmap->GetSpawnpoint_B();
	//player->Pos() = bossmap->GetSpawnpoint_P();
	player->Rot().y -= 1.575f;

	PLAYER = new Model("ProtectionWarrior");

	
	
}

MapTestScene::~MapTestScene()
{
	delete bossmap;
	delete Test;
}

void MapTestScene::Update()
{
	bossmap->Update();
	instaning->Update();
	player->Update();
	PLAYER->UpdateWorld();

	if (KEY_DOWN('1'))	bossmap->SetPhase(0);
	if (KEY_DOWN('2'))	bossmap->SetPhase(1);
	if (KEY_DOWN('3'))	bossmap->SetPhase(2);
	if (KEY_DOWN('4'))	bossmap->SetPhase(3);

	//Test->UpdateWorld();

	//if (bossmap->IsCollision(TestSize));
	if (bossmap->IsCollision(player->GetCollider())) 
	{
		player->Pos().y += 0.1f;
	};

	if (player->Pos().y < 0) player->Pos().y = 0;
}

void MapTestScene::Render()
{
	bossmap->Render();
	//Test->Render();
	instaning->Render();
	player->Render();
	PLAYER->Render();
}

void MapTestScene::PreRender()
{
}

void MapTestScene::PostRender()
{
}

void MapTestScene::GUIRender()
{
}
