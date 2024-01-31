#include "Framework.h"
#include "GBufferScene.h"

GBufferScene::GBufferScene()
{
    gBuffer = new GBuffer();

    forest = new Model("Forest");
    forest->UpdateWorld();
    human = new Human();

    //���۵� ���̴��� ��Ƽ���� ����
    // *���۵� ���̴� : ���̴��� �Է��� �޾��� ��, ���� ����� ������� �״�� �������� �ʰ�,
    //                 �߰� ������ �������� ������� ���ǿ� ���� �ٸ� ����� ����ϵ��� �ϴ� ���̴� ���
    //                 -> ���̴� ������ ������Ű�� ������ ��ó��, �� �� ������ �߰� ���� ���� �ϱ⿡ ����
    //                    ȭ�� ȭ���� �����ϰų�, Ư���� ȿ���� �ְų�, ȭ�鿡�� �ʿ��� ������ �����ų� �ϴ� �� ���δ�
    //                    ���� Ÿ�� � ����ϸ� Ư���� ������Ʈ�� �ƴ϶�, ���� ������ ������Ʈ��
    //                    ������ UI�� �ܵ����� ����ϰų�... ȭ���� ����� Ư���ϰ� ������ �� �ְ� �ȴ�

    // ��ü G���ۿ� ���۵� ���̴��� ����
    material = new Material(L"Light/Deferred.hlsl"); // <-���۵� ���̴�
    UINT vertices[4] = { 0, 1, 2, 3 };
    vertexBuffer = new VertexBuffer(vertices, sizeof(UINT), 4);
}

GBufferScene::~GBufferScene()
{
    delete gBuffer;
    delete forest;
    delete human;
    delete material;
    delete vertexBuffer;
}

void GBufferScene::Update()
{
    human->Update();
}

void GBufferScene::PreRender()
{
    //���� �� ��ġ

    gBuffer->SetMultiRenderTarget();

    // G���ۿ����� ������� ���۵� ���̴��� �𵨿� �����Ѵ�
    // * ���� ���� ���̴����� 11���� ���̴� ���Կ� ���� ��ǻ��ʸ�,
    //   12�� ����ŧ����, 13�� ��ָ� ��°���
    forest->SetShader(L"Light/GBuffer.hlsl");
    human->SetShader(L"Light/AnimGBuffer.hlsl");

    forest->Render();
    human->Render();
}

void GBufferScene::Render()
{
    vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    gBuffer->SetSRVs();
    material->Set();

    // ���� ���� �������ۿ� ���� ����� ���
    DC->Draw(4, 0);
}

void GBufferScene::PostRender()
{
    // ��������, �����ڿ��� �����ߴ� ��ó���� ���� ���̴��� ����� �����
    // ����� �� �� �ְ� �ȴ�
    // * ��ó���� ���� �׷��� ó���� �ɸ��� ���ϸ�, G ������ ���� �׷��� ó���� ��������ش�
    //   -> ���� ���� ȭ��, ���� ���� �׷��� ó���� ����
    gBuffer->PostRender();
}

void GBufferScene::GUIRender()
{
}
