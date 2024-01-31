#pragma once
class Naruto : public ModelAnimator
{
    // 나루토 : 모델 애니메이터 직접 상속
    //         -> 한 씬에 여러 명이 (지금은) 안 나와도 되니까
    //            * 이후 분신술 등을 쓴다든가 하면 그 때는 인스턴싱 고려 필요

private:

    //enum class STATE
    enum State
    {
        IDLE,
        RUN_F,
        RUN_B,
        RUN_L,
        RUN_R,
        THROW
        // 상태명의 기준 : fbx의 클립명 (첫 글자 대문자, 나머지 소문자. 예: "Dying")
        // * 나루토의 경우, 이 외에도 punching jump 같은 다른 클립이 있습니다만...
        //   여기선 일단 위에 적은 6가지 동작으로 클래스를 구성하겠습니다.
    };

public:

    Naruto();
    ~Naruto();

    void Update();
    void Render();
    void GUIRender();

private:
    // 조작을 받았을 때 움직이기
    void Control();
    void Move();
    void Rotate();
    void Attack();
    void SetAnimation();

    // 움직임 등의 변화에 따라 상태 바꾸기
    void SetState(State state);

    void Throw(); // 던지기
    void EndThrow(); // 던지기 동작(1회 수행, 클립 종료시 종료)이 끝났을 때

private:
    Transform* mainHand;
    Model* kunai; // <- 매니저 있지 않나???
                  //    모델을 이렇게 따로 가져오는 이유는 크게 2가지
                  //    1. 이 모델은 던지는 게 목적이 아닐 때 (손에 쥐고 있다든가...)
                  //    2. 꼭 이 모델을 쓰는 게 아니더라도, 로딩을 미리 해야 할 때

    State curState = IDLE;

    float moveSpeed = 500;
    float rotSpeed = 1;
    float deceleration = 5; // 디셀러레이션 : 감속
                            // -> 조작을 하다 말거나, 다른 이유로 이동이 멈출 때 즉시 멈추지 않고
                            //    속도를 떨어뜨려서 멈추게 할 때 사용하는 데이터
                            // 반대는 액셀러레이션 : 가속 (속도를 서서히 높여서 달릴 때 사용)

    Vector3 velocity;

    //POINT clientCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT / 2 }; // 아래와 100% 같은 코드
    POINT clientCenterPos = { WIN_WIDTH >> 1, WIN_HEIGHT >> 1 }; // A >> 1 : "A 나누기 2"의 비트연산
                                                                 // 2, 4, 8...혹은 정확한 값이 필요 없을 때
                                                                 // 5, 10 정도로 나누기에 좋은 빠른 연산
                                                                 // 정확한 연산이 필요할 때는 쓰면 안 된다
};

