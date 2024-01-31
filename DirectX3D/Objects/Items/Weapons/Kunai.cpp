#include "Framework.h"
#include "Kunai.h"

Kunai::Kunai(Transform* transform)
    : transform(transform)
{
    // ������ �ܰ迡�� Ʈ�������� ������ �޾Ƽ� �����Ѵ�
    // -> ���� �ۿ��� �����

    transform->Scale() = { 1, 1, 1 }; // ũ�� ���� (��ȭ�� �ʿ��ϸ� �ͼ� ���� �ʿ�)

    collider = new SphereCollider();
    collider->SetParent(transform); // �浹ü�� Ʈ�������� �����ϱ�

    collider->Scale() = { 1, 1, 1 }; // �浹ü ũ�� ���� (��ȭ�� �ʿ��ϸ� �ͼ� ����)
    collider->Pos() = {}; // ���� ��ġ ���� (�𵨰� �浹ü ���̿� ������ ������ ���⼭ ����
}

Kunai::~Kunai()
{
    delete collider;
}

void Kunai::Update()
{
    if (!transform->Active()) return; // Ȱ��ȭ�� �ƴϸ� ��������

    time += DELTA;

    if (time > LIFE_SPAN)
        transform->SetActive(false);

    transform->Pos() += direction * speed * DELTA;

    collider->UpdateWorld();
}

void Kunai::Render()
{
    collider->Render();
}

//�ۿ��� �θ��� ���� ��ô ���
void Kunai::Throw(Vector3 pos, Vector3 dir)
{
    transform->SetActive(true);

    transform->Pos() = pos;
    direction = dir;

    //transform->Rot().y = atan2(dir.x, dir.z) - XMConvertToRadians(90); //�Ʒ� �ڵ�� ����
    transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2;
                       // ���ư��� ����       -    90��
                       // (�Ϲ����� ���) ���η� ������� ����ü�� �յڷ� ������ ������ �� �ְ�

    time = 0; // ���� �ð��� 0
}
