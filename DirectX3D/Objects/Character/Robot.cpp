#include "Framework.h"

Robot::Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    : transform(transform) // Ʈ������
    , instancing(instancing) // �ν��Ͻ� ������
    , index(index)           // �ν��Ͻ� �� ����
{
    root = new Transform(); // ���� ���� �� ������ ����

    //�𵨿� ���ؼ� root�� �ٲ�� ���� �浹ü ����
    collider = new CapsuleCollider(30, 100); // ������, ���� ������ �Ű����� ����
    collider->SetParent(root); //������ ���� ��Ʈ�� ���⿡ �Ű������� ����
    collider->Rot().z = XM_PIDIV2 - 0.2f; //�ణ �������� �κ��� ����� �����ֱ� (�𵨺� �ɼ�)
    collider->Pos() = { -15.0f, 10.0f, 0.0f }; //�κ� ���� ���� ��ġ�� �浹ü �����ֱ� (�𵨿� ���� �ٸ� �ɼ�)

    //����
    motion = instancing->GetMotion(index);
    totalEvents.resize(instancing->GetClipSize());
    eventIters.resize(instancing->GetClipSize());

    //�̺�Ʈ ���� (���� ������� �͸�)
    SetEvent(STAND_UP, bind(&Robot::EndStandUp, this), 0.7f);
    SetEvent(HIT, bind(&Robot::EndHit, this), 0.9f);
    SetEvent(DYING, bind(&Robot::EndDying, this),  1);

    FOR(totalEvents.size())
    {
        eventIters[i] = totalEvents[i].begin();
    }

    velocity = Vector3(); // �ӷ� ���� �ʱ�ȭ

    //ĳ���Ϳ� UI �߰�
    hpBar = new ProgressBar(
        L"Textures/UI/hp_bar.png",
        L"Textures/UI/hp_bar_BG.png"
    );
}

Robot::~Robot()
{
    delete collider;
    delete root;
    delete hpBar;
}

void Robot::Update()
{
    // Ȱ��ȭ �߿��� �κ� �˰��� ������Ʈ
    if (!transform->Active()) return;

    //������Ʈ���� �ӷ� ���͸� ����ؾ� �Ѵٸ� ������ �ڵ带 Ȱ��ȭ
    // �׸��� Move() �� �ڵ带 ������ ��
    velocity = target->GlobalPos() - transform->GlobalPos();

    //������Ʈ�� �ʿ��� �Լ���
    Move();  // �̵�
    ExecuteEvent(); // �̺�Ʈ ����
    UpdateUI(); //UI ������Ʈ

    root->SetWorld(instancing->GetTransformByNode(index, 3)); //Robot ���� 3���� ��Ʈ ���
    collider->UpdateWorld(); // �浹ü ������Ʈ
}

void Robot::Render()
{
    //���� �� ����(��¥ ����) : �ν��Ͻ̿��� ���ٵ�
    collider->Render(); //�浹ü ����

}

void Robot::PostRender()
{
    //UI �߰�
    hpBar->Render();
}

void Robot::Hit(float amount)
{
    // ������ �ϰų� ���� �� ���� �Լ�
    // �ϴ� ������ �޴� �뵵�� (���ٸ� �߰� �Ű������� �� �־�� �� ��)

    //HP�� �������� ��ŭ ���
    curHP = curHP - amount;
    hpBar->SetAmount(curHP / maxHP); // ü�� ������ ���� ü�¹� ��ġ ����

    if (curHP <= 0)
    {
        SetState(DYING); // ü���� 0 ���ϸ� �װ� ����
        return;
    }

    // ������� ���� �¾Ұ�, ���� ��ƴ� �ִ�
    curState = HIT;
    instancing->PlayClip(index, HIT); // �� �ν��Ͻ̿��� "��" �κ��� ���� ��� ���
    eventIters[HIT] = totalEvents[HIT].begin(); // �ݺ��� �缳��

    // *���� : ���ݿ��� ���ٸ� �� �Լ��� A �������� (���ǹ��� ����) �� �Ʒ��� ���� �ڵ带 �߰�
    //         ...Ȥ�� ���Ѵٸ� ������ �Լ� �ۼ��ؼ� ȣ���ص� OK
}

void Robot::Spawn(Vector3 pos)
{
    transform->SetActive(true); //Ʈ������ Ȱ��ȭ
    collider->SetActive(true);

    SetState(WALK); // �ϴ� ������

    //ü�� ����
    curHP = maxHP;

    transform->Pos() = pos; //������ ��ġ��
}

void Robot::SetEvent(int clip, Event event, float timeRatio)
{
    if (totalEvents[clip].count(timeRatio) > 0) // �� ���ۿ�, ���� �������� ������ �̺�Ʈ�� �����̸�
        return; //����

    totalEvents[clip][timeRatio] = event; // �̺�Ʈ ����
}

void Robot::ExecuteEvent()
{
    // �� �ִϸ����Ϳ� �ִ� �̺�Ʈ ���� �Լ��� ����ϴ�
    // ���� �Լ��� ���ٰ� �򰥸��� �ٸ� ���� ���� ���� �ȴ�

    int index = curState; // ���� ���¸� �ӽ� �ε����� �ޱ�

    if (totalEvents[index].empty()) return; //���� ������ �̺�Ʈ�� 0���� ����
    if (eventIters[index] == totalEvents[index].end()) return; // �̺�Ʈ �ݺ��ڰ� ���̸� = �̺�Ʈ �������� ����

    float ratio = motion->runningTime / motion->duration; // (�ð�)���� = ����ð� / ��ü ����ð�

    if (eventIters[index]->first > ratio) return; // ���� �ð��� �� �� á���� ����

    //������� ���� �̺�Ʈ�� ����Ǿ�� �� �غ� ���� �� (�̺�Ʈ ����, �ð� �� ����)
    eventIters[index]->second(); // �̺�Ʈ�� ȣ��(����)
    eventIters[index]++;         // �ݺ��� �� ���� �ڷ� �ѱ��
                    //(�ܵ� �̺�Ʈ��� end(), ���� �ð��� ���� �̺�Ʈ�� �� �ִٸ� 2��°, 3��° ������...)
}

//��ü���� �̺�Ʈ��
void Robot::EndStandUp()
{
    //�Ͼ�� ������ ������ �����߰�, �Ͼ�� ������ �� �� ���� ��Ȳ
    // -> �ȱ� ����

    collider->SetActive(true); // Ȱ��ȭ�� �� �Ǿ��ٸ� ��Ű��
    SetState(WALK);
}

void Robot::EndHit()
{
    // �� �� ���� ��
    // -> �¾Ұ� ���� ��Ƶ� �ִ� �� (�׾��ٸ� Hit �Լ� ������ �״� �ڵ带 �������� �״ϱ�)

    SetState(WALK); // ��� �̵� (Move �Լ��� ���� ������ �ӷº��� ���� �ȱ�/�޸��� ������ �˾Ƽ� �Ѵ�)
}

void Robot::EndDying()
{
    // �׾����ϱ� �������� �ȴ�
    // �ð��� ������Ű�� ������ : �浹ü�� ���� ���� �ణ �ð��� �� �ְ� �ٸ� �Լ��� Ʈ���������� �����ָ� �ȴ�
    transform->SetActive(false);
    collider->SetActive(false);
}

void Robot::SetState(State state)
{
    if (state == curState) return;

    curState = state; //���� ����
    instancing->PlayClip(index, state); // ���� ����
    eventIters[state] = totalEvents[state].begin(); // �ݺ��� ����
}

void Robot::Move()
{
    //�κ��� �̵� �˰���

    if (curState == STAND_UP) return; // ���°� "������ �ֱ�"�� ����
    if (curState == HIT) return; // ���°� "�´� ��"�̾ ����
    if (curState == DYING) return; // ���°� "�׾��ų� �״� ��"�̾ ����
    if (velocity.Length() < 10) return; // �ӵ��� ������ ��� �� �߰�����(���⼭�� "������ �Ÿ�")�� �ʹ� ��� ����

    // ������� ���� �κ��� ����� �� ������ �� ���� �ʴ´�
    // -> �̵� ����

    // �ӷ��� ���� ������ ���� (�̵��� �������� �� �� ������ �Ǹ� ������Ʈ�� �� �ڵ� �ű� ��)
    //                       (....Ȥ�� �� �ڵ尡 �� �Լ� �ȿ� �������� ���� ���� if���� �浹 ���� ��쵵 ����)
    //velocity = target->GlobalPos() - transform->GlobalPos(); //ǥ���� �ڽ��� �Ÿ����迡 ���� �ӷ� ����

    // ǥ������ ������ ���� ������ õõ�� �ٰ�����, �Ÿ��� �������� �޷����
    if (velocity.Length() < 1000) //�ӷº����� ����(=ǥ������ ���� �Ÿ�)�� ������ �� �̸��̸�
    {
        moveSpeed = 100; //���� �̵� ����
        SetState(RUN); //���� : �޸���
    }
    else // �Ÿ��� �ʹ� �ָ�
    {
        moveSpeed = 50;
        SetState(WALK);
    }

    // ��ġ ���� �� ȸ�� ����ϱ�
    transform->Pos() += velocity.GetNormalized() * moveSpeed * DELTA;
    transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI; // �ӷº��Ϳ� ���� ȸ���� + �𵨿� ���� �������
}

void Robot::UpdateUI()
{
    barPos = transform->Pos() + Vector3(0, 180, 0); //Y 180 : ���� ũ�� (���� �ٲ�� ���ʵ� ����)

    hpBar->Pos() = CAM->WorldToScreen(barPos); // ������� ��ü�� 2D ȭ������ ����
                                               // UI�� ĵ�����̶�� �Ѵ�
    float scale = 100 / velocity.Length(); // ǥ������ �Ÿ��� ���� �׸� ũ�Ⱑ �޶�����

    scale = Clamp(0.1f, 1.0f, scale); // �ִ� �ּ� ������ ���� �ʰ�

    hpBar->Scale() = { scale, scale, scale };

    hpBar->UpdateWorld(); // ���� ������Ʈ
}
