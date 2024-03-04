#pragma once
class VAlkier : public MonsterBase
{
public:
    enum State
    {
        IDLE,
        FLYING
    };

public:
	VAlkier(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<CH_Base_ver2*> target);
	~VAlkier();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    // 데미지를 받기 위한 함수
    virtual void Hit(float amount = 1) override;
    // 발키리를 스폰하기 위한 함수
    virtual void Spawn(Vector3 pos) override;

public:
    // 애니메이션 종료 이벤트를 설정하기 위한 함수
    void SetEvent(int clip, Event event, float timeRatio);
    // 애니메이션 인스턴싱 관련 함수
    void ExecuteEvent();

    // 애니메이션을 설정하기 위한 함수
    void SetState(State state);

    // 발키리의 이동을 담당하는 함수
    void Move();
    // 발키리의 공격을 담당하는 함수
    void targetAttack();

private:
    State curState = IDLE;

private: // 공격을 위한 변수 모음
    bool TaxiMode = false;
    Collider* tong;

};