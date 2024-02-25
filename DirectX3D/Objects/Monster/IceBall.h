#pragma once
class IceBall : public MonsterBase
{
public:
    IceBall(vector<CH_Base_ver2*> target);
    ~IceBall();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    // 데미지를 받기 위한 함수
    virtual void Hit(float amount = 1) override;
    // 헤이트벡터의 순번을 지정하기 위한 임시변수
    int targetNumber = 0;
    virtual void Spawn(Vector3 pos) override;

public:
    void UpdateUI();

    void Move();
    void targetAttack();

private: // 공격을 위한 변수 모음
    Sphere* iceball;

    bool TaxiMode = false;

    ParticleSystem* particle;
    float Max_tickTime = 0.5f;
    float tickTime = Max_tickTime;
    Collider* nomarATK;
};