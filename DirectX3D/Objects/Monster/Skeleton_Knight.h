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

    Skeleton_Knight(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<CH_Base_ver2*> target);
    ~Skeleton_Knight();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    // 데미지를 받기 위한 함수
    virtual void Hit(float amount = 1) override;
    // 헤이트벡터의 순번을 지정하기 위한 임시변수
    int targetNumber = 0;
    virtual void Spawn(Vector3 pos) override;

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

    float Max_one_atk_time = 0.5f;
    float one_atk_time = Max_one_atk_time;
    bool isOne_sound = false;
};