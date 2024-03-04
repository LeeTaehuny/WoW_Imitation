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
    };

public:
	Boss_LichKing();
	~Boss_LichKing();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
    void PreRender();
    void GUIRender();

    // 리치왕을 스폰하기 위한 함수
    virtual void Spawn(Vector3 pos) override;
    // 데미지 정보를 받기 위한 함수
    virtual void Hit(float amount = 1) override;

    // 리치왕의 스탯정보를 받기 위한 함수
    Stat GetStat() { return Lich_Stat; }
    // 리치왕의 애니메이션을 설정하기 위한 함수
    void SetState(State state);

    // 캐릭터의 정보들을 저장하기 위한 변수
    vector<CH_Base_ver2*> characterData;

    // 보스맵의 정보를 내부에 저장하기 위한 함수
    void SetBossMap(class BossMap* map) { this->map = map; }

    // 패이즈 정보를 밖으로 내보내기 위한 함수
    UINT GetPhase() { return phase; }
    // 페이즈 정보를 설정하기 위한 함수
    void SetPhase(UINT num) { phase = num; }

    // 여러 정보들을 한 번에 초기화하기 위한 함수
    void resetBut();

private: // 멤버 변수
    // 리치왕의 움직임을 담당하는 함수
    void Moving();
    // 리치왕의 공격을 담당하는 함수
    void Attack();

    // 공격 모션이 끝났을때 실행되는 함수
    void End_ATK();
    // 히트 모션이 끝났을때 실행되는 함수
    void End_HIT();
    // 죽는 모션이 끝났을때 실행되는 함수
    void End_DIE();
    // 캐스팅 모션이 끝났을때 실행되는 함수
    void End_CAST();

    // 현재 타겟 캐릭터가 죽었을 경우 살아있는 캐릭터를 탐색하기 위한 함수
    void targetActiveSerch();

    // 1페이즈를 담당하는 함수
    void phaseOne();
    // 2페이즈를 담당하는 함수
    void phaseSait();
    // 3페이즈를 담당하는 함수
    void phaseTwo();
    // 4페이즈를 담당하는 함수
    void phaseSait2();
    // 5페이즈를 담당하는 함수
    void phaseThree();

private:
    ModelAnimator* lichking;

    Collider* Frost_Collider;
    State curState;
    int fom = 0;

    Transform* mainHand;
    Model* Frost;

private:
    Quad* frame;
    Quad* face;
    ProgressBar* hp_bar;
    SphereCollider* atk_serch;

    UINT phase = 1;
    float vidul;

    float Max_atk_del = 0.9f;
    float atk_del = Max_atk_del;
    int atk_one_sound = 0;
    float Max_atk_sound_Time = 0.5f;
    float atk_sound_Time = Max_atk_sound_Time;
    int hit_one_sound = 0;
    int die_one_sound = 0;

    class BossMap* map;

    Stat Lich_Stat;

    bool lasting = false;
    float Max_lasting_time = 1.5f;
    float lasting_time = Max_lasting_time;

    vector<UINT> character_Damage_Data;

    // 스킬을 저장하기 위한 벡터
    vector<class Lich_000_Base*> lich_SkillList;
    CH_Base_ver2* target;

private: // 두 번째 페이즈에서 사용하기 위한 변수들
    int first = 0;

    Collider* fieldzero;

private:
    // 2페이즈에서 외각의 얼음들을 떨어트리기 위한 변수
    int thr_first = 0;

private:
    // 사이 페이즈에서 외각의 얼음들을 복원시키기 위한 변수
    int for_first = 0;

private:

    // 마지막 페이즈에서 외각의 얼음들을 떨어트리게 하기 위한 변수
    int fiv_first = 0;
    // 마지막 페이즈에 돌입한 후 첫번째 스킬을 사용할때까지 걸리는 딜레이 시간
    float sumon1 = 3;
    // 마지막 페이즈에 돌입한 후 두번째 스킬을 사용할때까지 걸리는 딜레이 시간
    float skill1 = 7;

private:
    // 사이 페이즈에 돌입했을 경우 움직이거나 공격을 하지 못하도록
    // 하기위한 변수
    bool siitpha = false;

};