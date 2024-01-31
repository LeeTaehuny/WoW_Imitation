#pragma once

class Kunai
{
    // 투사체에 필요한 데이터

private:
    float LIFE_SPAN = 5.0f; // life span : 원문은 생애 주기.
                            // 프로그래밍에서는 생성된 객체의 지속 시간을 말한다 (주기가 끝나면 삭제)

public:
    Kunai(Transform* transform);
    ~Kunai();

    void Update();
    void Render();

    void Throw(Vector3 pos, Vector3 dir);

    SphereCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

private:

    // 모델 변수는 없음 : 외부에서 만들기

    Transform* transform;
    SphereCollider* collider;

    //진행속도
    float speed = 1000.0f;

    //현재 생성된 기간
    float time = 0;

    //방향
    Vector3 direction;
};

