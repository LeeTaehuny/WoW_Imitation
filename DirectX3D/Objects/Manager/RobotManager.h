#pragma once

class RobotManager : public Singleton<RobotManager>
{
private:
    UINT SIZE = 30; // �ִ� �� ��ü���� ������ ���ΰ� (���� ũ��)
    float SPAWN_TIME = 2.0f; // ���� Ȥ�� ������� �ʿ��� �ð� (����)

public:
    //�ܺ�ȣ���

    RobotManager();
    ~RobotManager();

    void Update();
    void Render();
    void PostRender();

    //�κ� Ȥ�� �κ����� ������ �Ѿư� ������ �Ŵ������� ���� �����ϵ���
    void SetTarget(Transform* target);

    //�� �κ��� �ٸ� �ܺ� �����Ϳ� �浹�ߴ��� ���� (�ǰ� Ȥ�� ����, Ȥ�� UI���ÿ�)
    bool IsCollision(Ray ray, Vector3& hitPoint);

private:
    //���θ���Լ�
    void Collision(); // �浹 ���� ����
    void Spawn(); // (��)����

private:
    //���θ������

    ModelAnimatorInstancing* robotInstancing;
    vector<Robot*> robots;

    Transform* target;

    float time = 0; // ��� �ð�

};

