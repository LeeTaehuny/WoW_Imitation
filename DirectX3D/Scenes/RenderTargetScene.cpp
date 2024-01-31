#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
    forest = new Model("Forest");
    forest->UpdateWorld();

    human = new Human();

    renderTarget = new RenderTarget();
    depthStencil = new DepthStencil();

    quad = new Quad(Vector2(500, 500)); //�ƹ��͵� ���� �簢�� ����� (�׸��� �ƴϴ�)
    quad->Pos() = { CENTER_X, CENTER_Y };
    quad->GetMaterial()->SetShader(L"PostEffect/Bloom.hlsl"); // "������" ȿ��: ��ó�� ���̴� �� �ϳ�
    quad->GetMaterial()->SetDiffuseMap(Texture::Add(L"Render", renderTarget->GetSRV()));
                     // �Ű������� "������� �̸����� ��Ī��, ���� Ÿ�� ��ü�� �ǽð� ���� ȭ��"
    quad->UpdateWorld();

    valueBuffer = new FloatValueBuffer(); //�� �Ҽ� ����� ���� ����
    valueBuffer->Get()[0] = 1;
    valueBuffer->Get()[1] = 1;
}

RenderTargetScene::~RenderTargetScene()
{
    delete forest;
    delete human;
    delete renderTarget;
    delete depthStencil;
    delete quad;
    delete valueBuffer;
}

void RenderTargetScene::Update()
{
    human->Update();
}

void RenderTargetScene::PreRender()
{
    renderTarget->Set(depthStencil); // ���� �����ص� ���� ���ٽ� ���� �̿��� ���� Ÿ�� ��� ����

    forest->Render(); // Ÿ������ ������ ����(����)�� �� �׸���
    human->Render(); //�ΰ� �׸���
    // -> ���� �ΰ��� ���忡 �׷ȴµ� ���� ���带 �� �׸��� ���繬�� �״� ���嵵 ���߿� ����
}

void RenderTargetScene::Render()
{
    // ���� ����
    human->Render();
}

void RenderTargetScene::PostRender()
{
    valueBuffer->SetPS(10);
    quad->Render(); // ����(���� Ÿ���� �����)�� ����
}

void RenderTargetScene::GUIRender()
{
    // Threshold : �Ӱ���. ������ �����̳� ó���� �Ͼ�� ���� �ּ�(Ȥ�� �ִ�)����
    //             �Ӱ����� �� ������ ������ �ƿ� ������� ����.
    //             ���ӿ����� �����̳� ���� ���� � ����ȴ�
    ImGui::SliderFloat("Threshold", &valueBuffer->Get()[0], 0, 1);

    // * �� �Ӱ����� ���� ���갪 : ������ ���̴��� ���� ���
    //   ���� ���� ��������(���� ����)�� ������ �� �̻��� �� (�� threshold�� ����)
    //   �� �ɼǿ��� ������ ��� ������ ��ȭ�� ��
    ImGui::SliderFloat("Value", &valueBuffer->Get()[1], 0, 10);
}
