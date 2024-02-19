#pragma once
class Boss_LichKing : public ModelAnimator
{
    enum State
    {
        WALKING,
        ATTACK_1,
        IDLE, HIT, DIE,
        CASTING,
    };

public:
	Boss_LichKing();
	~Boss_LichKing();

    void Update();
    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

    void SetState(State state);

    void Hit();

private:
    void End_ATK();
    void End_HIT();
    void End_DIE();
    void End_CAST();

private:
    State curState;
    int fom = 0;

    Transform* mainHand;
    Model* Frost;

private:
    UINT Max_hp = 17400000;
    UINT cur_hp = Max_hp;
    float Armor = 100;

    vector<float> character_Damage_Data;
};