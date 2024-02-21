#pragma once

class Boss_LichKing : public ModelAnimator
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
        UINT Max_hp = 17400000;
        UINT cur_hp = Max_hp;
        float damage = 300.0f;
        float Armor = 100.0f;
        float moveSpeed = 2.0f;
    };

public:
	Boss_LichKing();
	~Boss_LichKing();

    void Update();
    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

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

private:
    Collider* myCollider;
    Collider* Frost_Collider;
    Collider* atk_serch;
    State curState;
    int fom = 0;

    Transform* mainHand;
    Model* Frost;

private:

    Stat Lich_Stat;

    bool lasting = false;
    float Max_lasting_time = 3.0f;
    float lasting_time = Max_lasting_time;

    vector<UINT> character_Damage_Data;

    // 스킬을 저장하기 위한 벡터
    vector<class Lich_000_Base*> lich_SkillList;
    CH_Base_ver2* target;
};