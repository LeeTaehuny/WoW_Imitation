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
    // 헤이트벡터의 순번을 지정하기 위한 임시변수
    int targetNumber = 0;
    virtual void Spawn(Vector3 pos) override;

public:
    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();
    void UpdateUI();

    void EndDeath();

    void SetState(State state);

    void Move();
    void targetAttack();

private:
    State curState = IDLE;

private: // 공격을 위한 변수 모음
    bool TaxiMode = false;

};