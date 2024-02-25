#pragma once

class Boss_LichKing : public MonsterBase
{
    enum State
    {
        WALKING,
        ATTACK,
        IDLE, HIT, DIE,
        CASTING,
    };

    struct Stat
    {
        float damage = 300.0f;
        float Armor = 100.0f;
        float moveSpeed = 2.0f;
    };

public:
	Boss_LichKing();
	~Boss_LichKing();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
    void PreRender();
    void GUIRender();

    virtual void Spawn(Vector3 pos) override;
    virtual void Hit(float amount = 1) override;

    Stat GetStat() { return Lich_Stat; }
    void SetState(State state);

    void Hit(float damage, int targetNumber = 0);

    vector<CH_Base_ver2*> characterData;
private: // 멤버 변수
    void Moving();
    void Attack();

    void End_ATK();
    void End_HIT();
    void End_DIE();
    void End_CAST();

    void targetActiveSerch();

    void phaseOne();
    void phaseTwo();

private:
    ModelAnimator* lichking;

    Collider* Frost_Collider;
    Collider* atk_serch;
    State curState;
    int fom = 0;

    Transform* mainHand;
    Model* Frost;

private:

    UINT phase = 1;
    float vidul;

    Stat Lich_Stat;

    bool lasting = false;
    float Max_lasting_time = 3.0f;
    float lasting_time = Max_lasting_time;

    vector<UINT> character_Damage_Data;

    // 스킬을 저장하기 위한 벡터
    vector<class Lich_000_Base*> lich_SkillList;
    CH_Base_ver2* target;

private: // 두 번째 페이즈에서 사용하기 위한 변수들
    int first = 0;

    Collider* fieldzero;
};