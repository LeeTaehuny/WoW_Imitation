#include "Framework.h"

Naruto::Naruto()
    : ModelAnimator("Naruto")
{
    // Ŭ���̾�Ʈ ȯ���� ���ؼ� ȭ��� ����Ʈ ��ġ ������
    //ClientToScreen(hWnd, &clientCenterPos);
    //SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    // �� ���۽� ���콺 ��ġ�� ���� ������ �ڴ�� ���ư��� ���� ���̱� ����

    // �� ��(���⼱ ������) ������ ���� �տ� ����ֱ�
    mainHand = new Transform();
    kunai = new Model("Kunai");
    kunai->SetParent(mainHand);
    kunai->SetTag("Kunai");
    kunai->Load();

    // ���� �б�
    ReadClip("Idle");
    ReadClip("Run"); //RUN_F
    ReadClip("RunBack"); //RUN_B
    ReadClip("RunLeft"); //RUN_L
    ReadClip("RunRight"); //RUN_R
    ReadClip("Throw");

    //������(�� �ش��ϴ� �ε����� Ŭ��) ���ۿ� �̺�Ʈ �����ϱ�
    GetClip((int)THROW)->SetEvent(bind(&Naruto::Throw, this), 0.7f); // �������� "������" �Լ��� �̺�Ʈ�� ����
                                                                     // �ð��� ���ӽ��̶�� 0.7�� ��������
    GetClip((int)THROW)->SetEvent(bind(&Naruto::EndThrow, this), 1.0f);
}

Naruto::~Naruto()
{
    delete mainHand;
    delete kunai;
}

void Naruto::Update()
{
    Control(); //���� ����
    SetAnimation(); //���ۿ� ���� �ִϸ��̼� ���

    mainHand->SetWorld(GetTransformByNode(38)); // ����� 38��(fbx�� ���������� 39��°) Ʈ�������� �ַ� ���� ��

    //���� ������Ʈ ����
    ModelAnimator::Update();
    kunai->UpdateWorld();
}

void Naruto::Render()
{
    ModelAnimator::Render(); // �𵨷μ� ����
    kunai->Render(); // �տ� �� ���ǵ� ����
}

void Naruto::GUIRender()
{
    Model::GUIRender();
    kunai->GUIRender();
}

void Naruto::Control()
{
    //���� ��Ʈ���� ���� ���� �ۼ�
    //���⼭�� "����"�̶�� �̸� �Ʒ� �Ѱ���
    
    //Rotate(); // ȸ��
    Move();   // �̵�
    Attack(); // ���� (����� ��ô)
}

void Naruto::Move()
{
    if (curState == THROW) return; // ������ ���̸� ���� ���� ����

    bool isMoveZ = false; // ���� �̵� �� �ƴ�
    bool isMoveX = false; // �¿� �̵� �� �ƴ�

    if (KEY_PRESS('W'))
    {
        velocity.z += DELTA; // �ӵ�(���뺯��)�� ��Ÿ��ŭ ���İ� �ֱ�
        isMoveZ = true; //���� �̵� ���� ��
    }

    if (KEY_PRESS('S'))
    {
        velocity.z -= DELTA;
        isMoveZ = true; //���� �̵� ���� ��
    }

    if (KEY_PRESS('A'))
    {
        velocity.x -= DELTA;
        isMoveX = true; //�¿� �̵� ���� ��
    }

    if (KEY_PRESS('D'))
    {
        velocity.x += DELTA;
        isMoveX = true; //�¿� �̵� ���� ��
    }

    if (velocity.Length() > 1) //�ӵ��� ��ü ��ġ�� 1�� ������ (������ ǥ���� ������ ���̰� 1 �ʰ�)
        velocity.Normalize(); //����ȭ
    // ������ �Ÿ� : �� �ڵ尡 ���� ������....?

    if (!isMoveZ) // ���� �̵� ���� �ƴϸ�
        velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //������ ���� ����

    if (!isMoveX) // �¿��̵��� ����
        velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

    //�¿�ȸ���� ��İ�꿡 ���� ����� ���� ( = ���� ���ϱ�)
    Matrix rotY = XMMatrixRotationY(Rot().y);
    Vector3 direction = XMVector3TransformCoord(velocity, rotY); // ������ ������ ������ "����"�� ���� ���� ����

    Pos() += direction * -1 * moveSpeed * DELTA; //"����" ������ �̵�
    // * -1 : ĳ���Ͱ� �������� �־ (3D fbx�� nif ���� ���� ����� ��� ���� �Ͼ�� ��)
    // ** �� DX �Լ� ��� ������ "����" : ī�޶�κ��� �־����� ������ ���Ѵ�
    //                                  ��쿡 ���� �ش� ������ �������� �ۿ��ϱ⵵ �ϰ�, �ĸ����� �ۿ��ϱ⵵ �Ѵ�
    //                                  (�������� ���ؿ� ���� �ٴ� �̸��� �ٸ���)
}

void Naruto::Rotate()
{
    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y); // ���콺�� ������ ������ Ŀ�� ��ġ�� "�߰�"���� �缳��

    // ī�޶�� ĳ���͸� ���� ȸ�� (+���� ī�޶�� ī�޶� ���� �����̰� ���� ��)
    // -> ���� ī�޶� ������ ���߿� �ʿ��ϴ�!
    Rot().y += delta.x * rotSpeed * DELTA;
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
}

void Naruto::Attack()
{
    if (curState == THROW) return;

    if (KEY_DOWN(VK_LBUTTON))
    {
        SetState(THROW); // ������ ���� ����
    }
}

void Naruto::SetAnimation()
{
    if (curState == THROW) return;

    if (velocity.z > 0.1f) // ���� �ӵ��� �����̶� ������
        SetState(RUN_F);
    else if (velocity.z < -0.1f) // ������ ���´� �¿��̵� ���º��� �켱�Ѵٴ� �ڵ�
        SetState(RUN_B);
    else if (velocity.x < -0.1f) // �¿� �߿��� ���� �켱
        SetState(RUN_L);
    else if (velocity.x > 0.1f) // ������ ������
        SetState(RUN_R);
    else // 4�� ���� ��� �������� (����) ����
        SetState(IDLE);

    // *�� ���ǹ����� 0.1 �� �� ���� ���� �ٲ���� ������ �ڿ�������,
    //  ���� ��ȯ�� �ΰ��ϰ� ��쿡 ���� ���ڿ������� �� (�� ���̿��� �ڱ� ������ ã�ƾ� ��)
}

void Naruto::SetState(State state)
{
    if (state == curState) return;

    curState = state; //���� ���� ��
    PlayClip(state); // ����(Ŭ��)�� ���
}

void Naruto::Throw()
{
    // ���� ������ (�Ŵ��� ȣ��)
    KunaiManager::Get()->Throw(kunai->GlobalPos(), Back());
    // �Ű����� 1 : "�տ� �� ����"�� ��ġ�� �������� ��Ƽ� �ű⼭ ���̰� ���ư�����
    // �Ű����� 2 : FBX�� ����� ���� ������ �� ���� ���� �� �־
    //             (������� �ҷ����� ī�޶� ���� ���� ���� �ڱ��� �����̴�)
}

void Naruto::EndThrow()
{
    // �����Ⱑ ������ ���� �ٽ� ������ �ִ� �������� ����
    SetState(IDLE);
}