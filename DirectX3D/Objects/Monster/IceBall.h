#pragma once
class IceBall : public MonsterBase
{
public:
    IceBall(vector<CH_Base_ver2*> target);
    ~IceBall();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    // �������� �ޱ� ���� �Լ�
    virtual void Hit(float amount = 1) override;
    // ���͸� �����ϱ� ���� �Լ�
    virtual void Spawn(Vector3 pos) override;

public:
    // ���������� �������� ����� �Լ�
    void Move();
    // ���������� ������ ����� �Լ�
    void targetAttack();

private: // ������ ���� ���� ����
    Sphere* iceball;

    bool TaxiMode = false;

    ParticleSystem* particle;
    float Max_tickTime = 0.5f;
    float tickTime = Max_tickTime;
    Collider* nomarATK;
};