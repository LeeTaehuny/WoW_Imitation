#pragma once

class Kunai
{
    // ����ü�� �ʿ��� ������

private:
    float LIFE_SPAN = 5.0f; // life span : ������ ���� �ֱ�.
                            // ���α׷��ֿ����� ������ ��ü�� ���� �ð��� ���Ѵ� (�ֱⰡ ������ ����)

public:
    Kunai(Transform* transform);
    ~Kunai();

    void Update();
    void Render();

    void Throw(Vector3 pos, Vector3 dir);

    SphereCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

private:

    // �� ������ ���� : �ܺο��� �����

    Transform* transform;
    SphereCollider* collider;

    //����ӵ�
    float speed = 1000.0f;

    //���� ������ �Ⱓ
    float time = 0;

    //����
    Vector3 direction;
};

