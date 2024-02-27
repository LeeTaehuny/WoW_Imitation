#include "Framework.h"
#include "TownScene.h"
#include "Objects/Skills/SkillManager.h"
#include "Objects/MAP/TownMap.h"

TownScene::TownScene()
{
    // 맵 생성
    townMap = new TownMap();

    // 로딩 화면 생성
    loding = new Quad(Vector2(WIN_WIDTH, WIN_HEIGHT));
    loding->GetMaterial()->SetDiffuseMap(L"Textures/SelectScene/loding.jpg");
    loding->Pos() = Vector3(CENTER_X, CENTER_Y);
    loding->SetActive(false);
    loding->UpdateWorld();
}

TownScene::~TownScene()
{
    SAFE_DEL(townMap);
    SAFE_DEL(loding);
}

void TownScene::Start()
{
    // 위치 초기화
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
    for (int i = 0; i < CH->GetCharcterData().size(); i++)
    {
        int height = townMap->GetHeight(CH->GetCharcterData()[i]->Pos());
        CH->GetCharcterData()[i]->SetHeight(height);
    }
   
	CH->Update();
	SKILL->Update();

    MONSTER->Update();
    townMap->Update();

    Loding();
    
    if (townMap->isCollisionPortal())
    {
        // 로딩 화면 출력
        loding->SetActive(true);

        // 로딩을 위한 준비가 끝났다고 선언
        isReady = true;
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
    loding->Render();
}

void TownScene::GUIRender()
{
    townMap->GUIRender();
}

void TownScene::Loding()
{
    // 로딩 준비가 끝나지 않은 경우 반환
    if (!isReady) return;

    // 다음 씬으로 전환
    SceneManager::Get()->ChangeScene("Boss");
}
