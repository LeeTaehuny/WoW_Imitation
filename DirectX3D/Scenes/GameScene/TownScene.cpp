#include "Framework.h"
#include "TownScene.h"
#include "Objects/Skills/SkillManager.h"
#include "Objects/MAP/TownMap.h"

TownScene::TownScene()
{
    // 맵 생성
    townMap = new TownMap();
}

TownScene::~TownScene()
{
    SAFE_DEL(townMap);
}

void TownScene::Start()
{
	CH->GetPlayerData()->Pos() = Vector3(210.0f, 0.0f, 165.0f);
	CH->GetPlayerData()->Rot() = Vector3(0.0f, 7.3f, 0.0f);
	SKILL->Init(CH->GetPlayerData());
	CAM->SetTarget(CH->GetPlayerData());

    int height = townMap->GetHeight(Vector3(80.0f, 0.0f, 185.0f));
    MONSTER->SpawnScarecrow(Vector3(80.0f, height, 185.0f));
    MONSTER->SpawnScarecrow(Vector3(85.0f, height, 175.0f));
    MONSTER->SpawnScarecrow(Vector3(65.0f, height, 180.0f));
}

void TownScene::Update()
{
    int height = townMap->GetHeight(CH->GetPlayerData()->Pos());
    CH->GetPlayerData()->SetHeight(height);
   
	CH->Update();
	SKILL->Update();

    MONSTER->Update();
    townMap->Update();
    
    if (townMap->isCollisionPortal())
    {
        // TODO : 씬 전환
    }
}

void TownScene::PreRender()
{
}

void TownScene::Render()
{
    townMap->Render();
	CH->Render();

    MONSTER->Render();
}

void TownScene::PostRender()
{
	SKILL->PostRender();
    townMap->PostRender();
	CH->PostRender();
    MONSTER->PostRender();
}

void TownScene::GUIRender()
{
    townMap->GUIRender();
}
