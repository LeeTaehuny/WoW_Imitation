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
    // 몬스터를 스폰하기 위한 함수
    virtual void Spawn(Vector3 pos) override;

public:
    // 얼음구슬의 움직임을 담당할 함수
    void Move();
    // 얼음구슬의 공격을 담당할 함수
    void targetAttack();

private: // 공격을 위한 변수 모음
    Sphere* iceball;

    bool TaxiMode = false;

    ParticleSystem* particle;
    float Max_tickTime = 0.5f;
    float tickTime = Max_tickTime;
    Collider* nomarATK;
};