#pragma once

class KunaiManager : public Singleton<KunaiManager>
{
private:
    friend class Singleton;
    UINT SIZE = 30; // ���� ���� ���� ����

public:

    KunaiManager();
    ~KunaiManager();

    void Update();
    void Render();

    void Throw(Vector3 pos, Vector3 dir); // ���� ���̿��� ���� �Լ��� �����ϱ� ���� �Ű��Լ�
                                          // ĳ���ʹ� �� �Լ��� ����, �� �Լ��� ��¥ ���̸� ������

    bool IsCollision(Collider* collider);

private:

    //������ ���� �����ؼ� �����ϱ� ����...
    ModelInstancing* kunaiInstancing; // ������ ���� ��� �� �ν��Ͻ̸����� ���
                                      // (����ü�� �ִϸ��̼��� �ִ� ����� ModelAnimationInstancing Ŭ������ �ʿ��� ��)

    vector<Kunai*> kunaies; // ���� ������ �� Ŭ����

};

