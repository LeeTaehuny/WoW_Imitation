#include "Framework.h"
#include "Human.h"

Human::Human() : ModelAnimator("Human") //�θ� �� �����
{
    //���� �б�
    ReadClip("Idle", 1);
    ReadClip("Run", 1);
    ReadClip("Jump", 1);

    action = (ACTION)frameBuffer->Get().cur.clip; // ������ 0��=������ �ֱ�� �׼ǵ� ������ �ֱ�

    //���� ����
    crowbar = new Crowbar();
    crowbar->Load(); // ���� ���õ� ������ �ִ��� ���� ������ �б�

    //���⸦ �տ� ���
    mainHand = new Transform(); // Ʈ�������� �ִٴ� �͸� ���ϱ�
    crowbar->SetParent(mainHand); // ���� ��ġ = �� ��

    // ���� (���� ��� ������) ����
    //FOR(5)
    //{
    //    KUNAI kunai;
    //    kunai.model = new Model("Kunai");
    //    kunai.model->Scale() *= 10; // �޸��� ū�� ���̴� �ʹ� �۾Ƽ�
    //    kunai.main = new Kunai(kunai.model); //���� �����Ϳ� ���� Ʈ�������� �־ ����
    //    kunai.main->GetTransform()->SetActive(false); // �ϴ� ��Ȱ��ȭ
    //    kunais.push_back(kunai); //���Ϳ� �߰�
    //}


    // ���� (�Ŵ���) ����
    KunaiManager::Get(); // �ʼ��� �ƴѵ� �صθ� �÷��� ���� �� ������ ���� �� ����

    //-----------------------

    // ������ ������ ������ ����

    startEdge = new Transform();
    endEdge = new Transform();
    trail = new Trail(L"Textures/Effect/Trail.png", startEdge, endEdge, 10, 10.0f);
}

Human::~Human()
{
    delete crowbar;
    delete mainHand; // <- �̷��� ������ �Ǵ� ���� : �����ʹ� ������ �����Ͱ� ���ư��� �ʴ´�
                     // ���� �� �ڸ��� ������� ���ɼ��� ���� ��
                     // �׸��� �� "��"�� ��¥ �����ʹ� ���� ������ �� �ڸ��� ���� �ִ�

    delete trail;
    delete startEdge;
    delete endEdge;

    //FOR(5)
    //{
    //    delete kunais[i].main;
    //    delete kunais[i].model;
    //}   
}

void Human::Update()
{
    ClipSync();
    Control();
    Jump();

    // ������Ʈ���� �߿��� �� : 1. �� ���� �����ΰ� (�������뺸�� ���� �����ؾ� ��)
    //                        2. �׸��� �� ���� ��� �ִ°� (�׷��� �ű⿡ ���Ⱑ ���� �״ϱ�)

    mainHand->SetWorld(GetTransformByNode(51)); //Ʈ�������� ���� �Ҵ��ϱ�
    // GetTransformByNode : �� �ִϸ����Ϳ��� ������� "��忡 �Ҵ�� Ʈ������ �޾ƿ���"
    // �Ű����� 51 : Human.fbx ���� �������� �־��� ����� ����

    crowbar->Update();

    //���� �غ�
    startEdge->Pos() = crowbar->GlobalPos() + crowbar->Up() * 200.0f; // ������ ���� ���ð�
    endEdge->Pos() = crowbar->GlobalPos() - crowbar->Up() * 200.0f;   // = 100.0f
    // ���� ��ġ�� �� ��ġ�� �������� ��ġ�� ũ�⸦ �������� ����
    // ���ÿ��� ���� 100.0f : �������� �𵨿��� ������ ���� ũ��
    // (���� �ٲ�ų� ũ�Ⱑ �� ������ ����)

    //�غ��� ��Ʈ�Ӹ� Ʈ������ ������Ʈ
    startEdge->UpdateWorld();
    endEdge->UpdateWorld();

    ModelAnimator::Update(); //�������μ��� ������Ʈ ���� ����
                             //Ŭ�������� ������ ����Լ��� �ż� ���� �߻�

    trail->Update(); //�� + �������� ������Ʈ �� ������ ������Ʈ

    //�ӽ� ������Ʈ
    //FOR(5) kunais[i].model->UpdateWorld();
    //FOR(5) kunais[i].main->Update();

    // ���� (�Ŵ���) ������Ʈ
    KunaiManager::Get()->Update();
}

void Human::Render()
{
    crowbar->Render();

    ModelAnimator::Render();

    trail->Render();

    //�ӽ� ����
    //FOR(5) kunais[i].main->Render(); // <-������ ���� Ŭ���� �ȿ� �� ������ ����

    // ����(�Ŵ���) ����
    KunaiManager::Get()->Render();
}

void Human::GUIRender()
{
    crowbar->GUIRender();
    ModelAnimator::GUIRender();

    //�ӽ� ImGui
    //FOR(5) kunais[i].main->GetTransform()->GUIRender();
}

void Human::ClipSync()
{
    // ��� ���� ������ ������ �׼ǰ� �޶�����
    if ((ACTION)frameBuffer->Get().cur.clip != action)
    {
        // �ൿ�� �´� ���� ���
        PlayClip((int)action);
    }
}

void Human::Control()
{
    if (!isJump)
    {
        if (KEY_PRESS('W'))
        {
            action = ACTION::RUN;
        }

        if (KEY_DOWN(VK_SPACE))
        {
            action = ACTION::JUMP;
            jumpVelocity = jumpForce;
            isJump = true;
        }

        if (KEY_UP('W'))
        {
            action = ACTION::IDLE;
        }

        if (KEY_DOWN(VK_RETURN))
        {
            //kunais[NextKunai()].main->Throw(Pos(), Forward());

            KunaiManager::Get()->Throw(Pos(), Forward());
        }
    }
}

void Human::Jump()
{
    jumpVelocity -= 9.8f * gravityMult * DELTA;
    Pos().y += jumpVelocity;

    if (Pos().y > 0)
    {
        if (action != ACTION::JUMP) action = ACTION::JUMP;
        isJump = true;
    }

    if (Pos().y < 0)
    {
        Pos().y = 0;
        jumpVelocity = 0;
        if (action == ACTION::JUMP) action = ACTION::IDLE;
        isJump = false;
    }
}
