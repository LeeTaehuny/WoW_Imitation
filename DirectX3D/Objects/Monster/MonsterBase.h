#pragma once
class MonsterBase
{
public:
    // 몬스터의 피격 콜라이더
    CapsuleCollider* collider;

protected:

    // 타겟의 콜라이더를 받아옴 (나중에 변경 가능)
    vector<Collider*> target;
    // 현재 타겟의 정보를 받아옴 (공격을 위한 변수)
    Collider* targetTransform;
    // 현재 움직일 수 있는가를 판별하는 변수 (거짓이면 움직이지 못함)
    bool Moving = true;
    // 타겟의 번호에 따라 헤이트 리스트가 배정되며 헤이트가 높은 적을
    // 추격하도록 하기위한 변수
    vector<float> targetHate;

    Transform* transform;
    // 공격범위 콜라이더 (충돌시 공격 모션 재생)
    SphereCollider* attackRange;
    BoxCollider* attackBumwe;

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
    

    vector<map<float, Event>> totalEvents;
    vector<map<float, Event>::iterator> eventIters;
};