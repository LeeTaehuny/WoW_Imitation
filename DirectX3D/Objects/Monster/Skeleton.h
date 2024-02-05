#pragma once
class Skeleton : public MonsterBase
{
public:
    enum State
    {
        IDLE,
        ATTACK1, ATTACK2,
        WALKING, RUN,
        DEATH, HIT, SCREAM,
    };

public:

    Skeleton(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<Collider*> target);
    ~Skeleton();

    void Update();
    void Render();
    void PostRender();

    // 데미지를 받기 위한 함수
    void Hit(float amount = 1, int targetNumber = 0);
    // 헤이트벡터의 순번을 지정하기 위한 임시변수
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

    // 적을 추격하는 함수
    void Move();
    // 공격범위 콜라이더에 충돌한 적을 공격을 담당하는 함수
    void targetAttack();

private:
    State curState = IDLE;
};