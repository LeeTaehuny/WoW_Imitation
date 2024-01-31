#include "Framework.h"
#include "IntancingScene.h"

IntancingScene::IntancingScene()
{
    
    // �� (���� ����) ����

    models = new ModelAnimatorInstancing("Naruto"); // �ִϸ����� �ϳ��� ��ó�� �ϴ� �����

    //�������� ���
    models->ReadClip("Idle");       // ���� �ڼ�
    models->ReadClip("Punching");   // �ָ���

    //�ΰ�(�׽�Ʈ)�� ���
    //models->ReadClip("Idle", 1); // �޸� FBX�� ���ۿ� ���� ������ �־ 1 �Ű����� �ʿ� (�ٸ� ���� ��� �� �� ����)
    //models->ReadClip("Run", 1);

    // (�ν��Ͻ� �ٽ�) ������� ������ ���� ũ�⸸ŭ �ν��Ͻ��� �߰� ����
    for (float z = 0; z < SIZE; ++z)
    {
        for (float x = 0; x < SIZE; ++x)
        {
            Transform* transform = models->Add();
                // �ν��Ͻ��� "�߰�" �Լ��� ���ؼ� ������ ����, ������ ����, ������ �ؽ�ó��
                // ��ġ, ����, ID ������ �ٸ� �� ��ü�� �����
            transform->Pos() = { x, 0, z }; //�� ��ü ��ġ ���ϱ�
            transform->Scale() *= 0.01f; //�߰��� ��ü�� 0.01�� ũ��
        }
    }

}

IntancingScene::~IntancingScene()
{
    delete models; // ���� ����� (�������� �� �� �����͸� ���ϱ�)
}

void IntancingScene::Update()
{
    models->Update(); // �ȿ� �ִ� ������ ���
}

void IntancingScene::PreRender()
{
}

void IntancingScene::Render()
{
    models->Render(); // ����Ǵ� ������ �ϳ��� ��ó�� ��� ��, �� ���� ��ü�� ��ġ���� ��¸�
}

void IntancingScene::PostRender()
{
}

void IntancingScene::GUIRender()
{
    ImGui::SliderInt("ID", &instanceID, 0, 100); // Ȯ���� �ν��Ͻ��� ID
    ImGui::SliderInt("Clip", &clip, 0, 1);       // �����ų ����

    if (ImGui::Button("Play")) //�÷��� ��ư ���� �� �ش� ��ư�� ������
    {
        models->PlayClip(instanceID, clip); // ������ id �ν��Ͻ��� ������ ���� �����Ű��
    }
    models->GUIRender();// �� �� UI ���� ����

}
