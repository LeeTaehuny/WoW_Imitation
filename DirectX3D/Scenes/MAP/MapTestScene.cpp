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
	bossmap->Scale() *= 10;
}

MapTestScene::~MapTestScene()
{
	delete bossmap;
	delete Test;
}

void MapTestScene::Update()
{
	bossmap->Update();

	if (KEY_DOWN('1'))	bossmap->SetPhase(0);
	if (KEY_DOWN('2'))	bossmap->SetPhase(1);
	if (KEY_DOWN('3'))	bossmap->SetPhase(2);
	if (KEY_DOWN('4'))	bossmap->SetPhase(3);

	//Test->UpdateWorld();
}

void MapTestScene::Render()
{
	bossmap->Render();
	//Test->Render();
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
