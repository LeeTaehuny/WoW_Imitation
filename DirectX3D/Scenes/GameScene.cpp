#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
    background = new Model("Forest");
    background->SetShader(L"Basic/Texture.hlsl");
    background->Scale() *= 10.0f;
    background->UpdateWorld();

    naruto = new Naruto();

    FOR(2)
        blendState[i] = new BlendState();
    // 주어진 알파를 다른 이미지와 혼합해서 최종 적용하기 위한(덮어씌우기 위한) 표제 색으로
    blendState[1]->AlphaToCoverage(true);

    //CAM->SetTarget(naruto);
    ////CAM->TargetOptionLoad("Follow");
    //CAM->TargetOptionLoad("Naruto");
    //CAM->LookAtTarget(); //카메라의 2차 초점을 표적에게 (락온 켜기 // *락온의 대상이 주인공이면? ...백뷰)

    skybox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
    skybox->UpdateWorld();

    //게임 내 싱글턴 사용 시 호출생성 혹은 초기화 함수 사용
    KunaiManager::Get();
    RobotManager::Get()->SetTarget(naruto);
}

GameScene::~GameScene()
{
    delete naruto;
    delete background;

    FOR(2)
        delete blendState[i];

    delete skybox;

    // 게임 내에서 싱글턴이 처음 사용된 경우 삭제
    KunaiManager::Delete();
    RobotManager::Delete();
}

void GameScene::Update()
{
    naruto->Update();

    KunaiManager::Get()->Update();
    RobotManager::Get()->Update();
}

void GameScene::PreRender()
{
}

void GameScene::Render()
{
    skybox->Render();

    naruto->Render();

    blendState[1]->SetState(); // 지금 나올 이미지는 다른 이미지와 통합 + 지정된 배경 색이 있으면 지우기
    background->Render();      // 그 다음에 배경 출력
    blendState[0]->SetState(); // 다시 이전처럼 (스테이트 옵션 없음)

    KunaiManager::Get()->Render();
    RobotManager::Get()->Render();
}

void GameScene::PostRender()
{
    //naruto->PostRender();
    RobotManager::Get()->PostRender();
}

void GameScene::GUIRender()
{
    naruto->GUIRender();
}
