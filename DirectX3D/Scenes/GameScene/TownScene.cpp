#include "Framework.h"
#include "TownScene.h"
#include "Objects/Skills/SkillManager.h"
#include "Objects/UI/PartyUI_Bar.h"
#include "Objects/UI/PlayerUI_Bar.h"
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

    // 음원 등록
    Audio::Get()->Add("TownBGM", "Sounds/TownScene/TownBGM.wav", true, true, false);
    Audio::Get()->Add("OpenUI", "Sounds/Basic/open.ogg", false, false, false);
    Audio::Get()->Add("SelectNPC", "Sounds/TownScene/npcSelect.wav", false, false, false);
}

TownScene::~TownScene()
{
    SAFE_DEL(townMap);
    SAFE_DEL(loding);
}

void TownScene::Start()
{
    // 위치 초기화 & 체력 초기화
    CH->GetPlayerData()->SetActive(true);
    CH->GetPlayerData()->GetCollider()->SetActive(true);
    CH->GetPlayerData()->GetStat().hp = CH->GetPlayerData()->GetStat().maxHp;
    CH->GetPlayerData()->GetStat().mp = CH->GetPlayerData()->GetStat().maxMp;
    CH->GetPlayerData()->GetPlayerUI()->SetHpPercent(1.0f);
    CH->GetPlayerData()->GetPlayerUI()->SetMpPercent(1.0f);
    CH->GetPlayerData()->Pos() = Vector3(210.0f, 0.0f, 165.0f);
    CH->GetPlayerData()->Rot() = Vector3(0.0f, 7.3f, 0.0f);
    CAM->SetTarget(CH->GetPlayerData());

    // 몬스터 생성
    if (MONSTER->GetScarecrow().size() == 0)
    {
        // 몬스터가 존재하지 않는 경우 스폰
        int height = townMap->GetHeight(Vector3(80.0f, 0.0f, 185.0f));
        MONSTER->SpawnScarecrow(Vector3(80.0f, height, 185.0f));
        MONSTER->SpawnScarecrow(Vector3(85.0f, height, 175.0f));
        MONSTER->SpawnScarecrow(Vector3(65.0f, height, 180.0f));
    }
    else
    {
        // 몬스터가 존재하는 경우 액티브 On
        for (int i = 0; i < MONSTER->GetScarecrow().size(); i++)
        {
            // 액티브 켜기
            MONSTER->GetScarecrow()[i]->GetTransform()->SetActive(true);
        }
    }

    // NPC 초기화
    if (CH->GetCharcterData().size() > 1)
    {
        for (int i = 1; i < CH->GetCharcterData().size(); i++)
        {
            // 액티브 ON
            CH->GetCharcterData()[i]->SetActive(true);
            CH->GetCharcterData()[i]->GetCollider()->SetActive(true);
            
            // 체력&마나 초기화
            CH->GetCharcterData()[i]->GetStat().hp = CH->GetCharcterData()[i]->GetStat().maxHp;
            CH->GetCharcterData()[i]->GetStat().mp = CH->GetCharcterData()[i]->GetStat().maxMp;
            CH->GetPartyUI()->SetHpPercent(1.0f, stoi(CH->GetCharcterData()[i]->GetTag().c_str()));

            // 위치 초기화
            CH->GetCharcterData()[i]->Pos() = CH->GetPlayerData()->Pos();
            CH->GetCharcterData()[i]->Pos().y = townMap->GetHeight(Vector3(80.0f, 0.0f, 185.0f));
        }
    }
    
    // 로딩 화면 출력 X
    loding->SetActive(false);
    isReady = false;

    // 음원 재생
    Audio::Get()->Play("TownBGM", 0.7f);
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
    if (loding->Active())
    {
        loding->Render();
    }
    else
    {
        SKILL->PostRender();
        townMap->PostRender();
        CH->PostRender();
        MONSTER->PostRender();
    }
}

void TownScene::GUIRender()
{
    townMap->GUIRender();
    CH->GUIRender();
}

void TownScene::Loding()
{
    // 로딩 준비가 끝나지 않은 경우 반환
    if (!isReady) return;

    // 음원 정지
    Audio::Get()->Stop("TownBGM");    

    // 몬스터 액티브 Off
    for (int i = 0; i < MONSTER->GetScarecrow().size(); i++)
    {
        // 체력 최대치로 설정
        MONSTER->GetScarecrow()[i]->SetCurHp(MONSTER->GetScarecrow()[i]->GetMaxHP());

        // 액티브 끄기
        MONSTER->GetScarecrow()[i]->GetTransform()->SetActive(false);
    }

    // 다음 씬으로 전환
    SceneManager::Get()->ChangeScene("DungeonScene");
    //SceneManager::Get()->ChangeScene("Boss");
}
