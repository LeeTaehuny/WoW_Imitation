#pragma once
class Scarecrow : public MonsterBase
{
public:
    enum State
    {
        IDLE,
        HIT,
    };

public:

    Scarecrow(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<Collider*> target);
    ~Scarecrow();

    void Update();
    void Render();
    void PostRender();

    // �������� �ޱ� ���� �Լ�
    void Hit(float amount = 1, int targetNumber = 0);
    // ����Ʈ������ ������ �����ϱ� ���� �ӽú���
    int targetNumber = 0;
    void Spawn(Vector3 pos);

    int GetmyNumber() { return index; }
    CapsuleCollider* GetCollider() { return collider; }

public:
    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();

    void EndHit();

    void SetState(State state);

private:
    State curState = IDLE;
};