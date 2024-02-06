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

    void EndHit();

    void SetState(State state);

private:
    State curState = IDLE;
};