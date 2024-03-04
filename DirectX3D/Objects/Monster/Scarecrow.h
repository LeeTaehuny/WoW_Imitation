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

    Scarecrow(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<CH_Base_ver2*> target);
    ~Scarecrow();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    // 데미지를 받기 위한 함수
    virtual void Hit(float amount = 1) override;
    // 허수아비를 스폰하기 위한 함수
    virtual void Spawn(Vector3 pos) override;

public:
    // 애니메이션 이벤트를 등록하기 위한 함수
    void SetEvent(int clip, Event event, float timeRatio);
    // 애니메이션 인스턴싱 관련 함수
    void ExecuteEvent();

    // 히트 애니메이션이 끝났을 경우
    void EndHit();

    // 애니메이션 변경을 위한 함수
    void SetState(State state);

private:
    State curState = IDLE;
};