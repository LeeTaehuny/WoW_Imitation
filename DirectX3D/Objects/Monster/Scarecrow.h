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

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    // 데미지를 받기 위한 함수
    virtual void Hit(float amount = 1, int targetNumber = 0) override;
    // 헤이트벡터의 순번을 지정하기 위한 임시변수
    int targetNumber = 0;
    virtual void Spawn(Vector3 pos) override;

public:
    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();

    void EndHit();

    void SetState(State state);

private:
    State curState = IDLE;
};