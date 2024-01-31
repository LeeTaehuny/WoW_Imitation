#pragma once
class Robot
{
private:
    //enum class STATE // <- 이 경우 클래스명 "STATE" 사용이 강제
                       //    단점 : 타자가 귀찮고 참조 속도도 (아주 아주 조금) 느리다
                       //  **장점** : enum 값이 중복될 때, 반드시 의도한 값을 호출 가능
    enum State
    {
        STAND_UP,
        WALK,
        RUN,
        HIT,
        DYING,
        // 상태명의 기준 : fbx의 클립명 (첫 글자 대문자, 나머지 소문자. 예: "Dying")
    };

public:
    Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~Robot();

    void Update();
    void Render();
    void PostRender(); //캐릭터에 종속된 UI가 있다면 여기서 추가

    void Hit(float amount = 1); // 공격과 피격
    void Spawn(Vector3 pos); // 개체 생성 (과 배치)

    //SphereCollider* GetCollider() { return collider; }
    CapsuleCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

    void SetTarget(Transform* target) { this->target = target; }

private:
    //멤버 함수 (내부용)

    void SetEvent(int clip, Event event, float timeRatio); //(모델 동작처럼) 이벤트 지정하기
    void ExecuteEvent(); // 이벤트 실행하기

    //동작이 끝날 때를 지정한 함수들
    void EndStandUp();
    void EndHit();
    void EndDying();

    void SetState(State state);

    void Move();
    void UpdateUI();

private:

    Transform* transform;
    //SphereCollider* collider; // 인간형 액터에게 구체 충돌체는 조금 크다
    CapsuleCollider* collider;   // 캡슐 콜라이더

    //모델을 쿠나이처럼 밖에서 만들고 총괄관리
    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    //모델의 구체적인 데이터
    Transform* root;    // 자기 모델의 최고외 메쉬(루트)
    Transform* target;  // 로봇의 표적 (인식 거리 안쪽이면 쫓아가야 할 대상)

    //액터의 UI
    ProgressBar* hpBar;
    Vector3 barPos; //체력바의 위치를 수치화한 것 (진짜 위치를 위한 중간계산용)

    float moveSpeed = 30;
    float maxHP = 10;
    float curHP = 10;

    Vector3 velocity; // 점프에 써도 되지만 아니어도 되는 범용 변수
                      // 움직일 때, 아닐 때 등등에 전부 사용 가능
    
    UINT index;
    State curState = STAND_UP; // 일단 가만히

    vector<map<float, Event>> totalEvents;
    vector<map<float, Event>::iterator> eventIters;
};