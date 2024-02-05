#pragma once
class Skeleton_Knight : public MonsterBase
{
public:
    enum State
    {
        IDLE,
        ATTACK1,
        WALKING,
        DEATH, HIT,
    };

public:

    Skeleton_Knight(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<Collider*> target);
    ~Skeleton_Knight();

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
    void UpdateUI();

    void EndAttack();
    void EndHit();
    void EndDeath();

    void SetState(State state);

    // ���� �߰��ϴ� �Լ�
    void Move();
    // ���ݹ��� �ݶ��̴��� �浹�� ���� ������ ����ϴ� �Լ�
    void targetAttack();

private:
    State curState = IDLE;
};