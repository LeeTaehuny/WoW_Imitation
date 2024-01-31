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
    // �־��� ���ĸ� �ٸ� �̹����� ȥ���ؼ� ���� �����ϱ� ����(������ ����) ǥ�� ������
    blendState[1]->AlphaToCoverage(true);

    //CAM->SetTarget(naruto);
    ////CAM->TargetOptionLoad("Follow");
    //CAM->TargetOptionLoad("Naruto");
    //CAM->LookAtTarget(); //ī�޶��� 2�� ������ ǥ������ (���� �ѱ� // *������ ����� ���ΰ��̸�? ...���)

    skybox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
    skybox->UpdateWorld();

    //���� �� �̱��� ��� �� ȣ����� Ȥ�� �ʱ�ȭ �Լ� ���
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

    // ���� ������ �̱����� ó�� ���� ��� ����
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

    blendState[1]->SetState(); // ���� ���� �̹����� �ٸ� �̹����� ���� + ������ ��� ���� ������ �����
    background->Render();      // �� ������ ��� ���
    blendState[0]->SetState(); // �ٽ� ����ó�� (������Ʈ �ɼ� ����)

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
