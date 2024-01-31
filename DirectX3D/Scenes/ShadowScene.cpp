#include "Framework.h"
#include "ShadowScene.h"

ShadowScene::ShadowScene()
{
    forest = new Model("Forest");
    forest->UpdateWorld();
    human = new Human();

    shadow = new Shadow();

    //�� ���� ȣ��
    LightBuffer::Light* light = Environment::Get()->GetLight(0);
    light->type = 1;
    light->pos = { 0, 750, -500 }; // ������ ��ġ (ū �ǹ̴� ���� �� ������)
    light->range = 2000;           // ���� ��� �Ÿ�
}

ShadowScene::~ShadowScene()
{
    delete forest;
    delete human;

    delete shadow;

}

void ShadowScene::Update()
{
    human->Update();
}

void ShadowScene::PreRender()
{
    //�׸��� Ŭ������ ���� Ÿ�� ������� ����
    shadow->SetRenderTarget();

    //�ΰ����� ���� ���ٽ�(����/���� ����) ������ ����
    human->SetShader(L"Light/DepthMap.hlsl");

    //������ 1ȸ ����
    human->Render();
}

void ShadowScene::Render()
{
    shadow->SetRender(); // �׸��� ����(�� �Լ����� ����� ��)�� �̸� ����

    // �׸��� �������� �ٽ� ���� (�ΰ��� ���⼭ 2ȸ° ����)
    // �غ�� �𵨵鿡�� �׸��� ���ο� ũ�⸦ �����ϴ� ����(�׸��ڸ� ������ �𵨿� ���̴�) �߰�
    forest->SetShader(L"Light/Shadow.hlsl");
    human->SetShader(L"Light/Shadow.hlsl");

    //���⼭ ��¥ ���� ȣ��
    forest->Render();
    human->Render();
}

void ShadowScene::PostRender()
{
    shadow->PostRender(); // ȣ���ؼ� �Լ� ���� ����
}

void ShadowScene::GUIRender()
{
    shadow->GUIRender();
}
