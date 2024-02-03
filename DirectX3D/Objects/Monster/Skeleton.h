#pragma once
class Skeleton
{
public:
    enum State
    {
        IDLE,
        ATTACK1, ATTACK2,
        WALKING, RUN,
        DEATH, HIT, SCREAM,
    };

public:

    Skeleton(Transform* transform, ModelAnimatorInstancing* instancing, UINT index, vector<Collider*> target);
    ~Skeleton();

    void Update();
    void Render();
    void PostRender();

    // 데미지를 받기 위한 함수
    void Hit(float amount = 1, int targetNumber = 0);
    // 헤이트벡터의 순번을 지정하기 위한 임시변수
    int targetNumber = 0;
    void Spawn(Vector3 pos);

    int GetmyNumber() { return index; }
    CapsuleCollider* GetCollider() { return collider; }

public:
    void SetEvent(int clip, Event event, float timeRatio);
    void ExecuteEvent();
    void UpdateUI();

    void EndAttack();
    void EndHit();
    void EndDeath();

    void SetState(State state);

    // 적을 추격하는 함수
    void Move();
    // 공격범위 콜라이더에 충돌한 적을 공격을 담당하는 함수
    void targetAttack();

    // 타겟의 콜라이더를 받아옴 (나중에 변경 가능)
    vector<Collider*> target;   
    // 현재 타겟의 정보를 받아옴 (공격을 위한 변수)
    Collider* targetTransform;  
    // 현재 움직일 수 있는가를 판별하는 변수 (거짓이면 움직이지 못함)
    bool Moving = true;
    // 타겟의 번호에 따라 헤이트 리스트가 배정되며 헤이트가 높은 적을
    // 추격하도록 하기위한 변수
    vector<float> targetHate;
private:
    Transform* transform;
    // 몬스터의 피격 콜라이더
    CapsuleCollider* collider;
    // 공격범위 콜라이더 (충돌시 공격 모션 재생)
    SphereCollider* attackRange;

    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    Transform* root;

    float moveSpeed = 30;
    float maxHP = 10;
    float curHP = 10;

    // 방향
    Vector3 velocity;

    UINT index;
    // 현재 재생중인 애니메이션
    State curState = IDLE;

    vector<map<float, Event>> totalEvents;
    vector<map<float, Event>::iterator> eventIters;
};