#include "Framework.h"
#include "Crowbar.h"

Crowbar::Crowbar() : Model("crowbar")
{
    SetTag("Crowbar");

    //�浹ü �����ϱ�
    collider = new BoxCollider();
    collider->SetTag("CrowbarCollider"); // �±� ���ϱ� (�θ�� ���� Ű���带 �����ϸ� ����)
    collider->SetParent(this);           // �θ� ���ϱ�
    collider->Load();                    // Ʈ������ ���� �ε��ϱ� (������ �ִٸ�)
}

Crowbar::~Crowbar()
{
    delete collider;
}

void Crowbar::Update()
{
    UpdateWorld(); // �ڱ� ������Ʈ
    collider->UpdateWorld(); //�浹ü�� ������Ʈ
}

void Crowbar::Render()
{
    Model::Render(); // �ڱ� ����
    collider->Render(); // �浹ü ����
}

void Crowbar::GUIRender()
{
    Model::GUIRender();
    collider->GUIRender();
}
