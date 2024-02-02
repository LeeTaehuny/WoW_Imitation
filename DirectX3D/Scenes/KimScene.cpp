#include "Framework.h"
#include "KimScene.h"

KimScene::KimScene()
{
	mainPlayer = new ProtectionWarrior();

	coll = new BoxCollider();
	coll->Pos() = Vector3(5);
}

KimScene::~KimScene()
{
	delete mainPlayer;
	delete coll;
}

void KimScene::Update()
{
	//mainPlayer->OnHit(coll);
	if (KEY_DOWN('Z')) mainPlayer->isCasting = true;

	mainPlayer->PlayerUpdate();
	coll->UpdateWorld();
}

void KimScene::PreRender()
{
}

void KimScene::Render()
{
	mainPlayer->Render();
	coll->Render();
}

void KimScene::PostRender()
{
}

void KimScene::GUIRender()
{
	mainPlayer->GUIRender();
	coll->GUIRender();
}
