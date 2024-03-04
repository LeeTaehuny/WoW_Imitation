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
    // 스켈레톤 나이트를 스폰하기 위한 함수
    virtual void Spawn(Vector3 pos) override;

public:
    // 애니메이션 종료 이벤트를 설정하기 위한 함수
    void SetEvent(int clip, Event event, float timeRatio);
    // 애니메이션 인스턴싱 관련 함수
    void ExecuteEvent();

    // 공격 애니메이션이 종료되었을때 실행되는 함수
    void EndAttack();
    // 히트 애니메이션이 종료되었을때 실행되는 함수
    void EndHit();
    // 데스 애니메이션이 종료되었을때 실행되는 함수
    void EndDeath();

    // 애니메이션을 변경하기 위한 함수
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