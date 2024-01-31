#pragma once
class Human : public ModelAnimator
{
private:
    enum class ACTION
    {
        IDLE,
        RUN,
        JUMP
    };

public:
    Human();
    ~Human();

    void Update();
    void Render();
    void GUIRender();

private:
    // 나중에 자식 개체가 붙거나 별도 연산 대상이 생기면 코드 추가
    // 자식 개체 : 모자, 배낭, 방탄조끼, 손에 든 무기 등
    // 별도연산 대상 : 발소리 체크를 위한 "내 발" 혹은 무기를 쥐기 위한 "내 손"

    // 예 : 쇠지렛대를 무기로 사용해, 손에 쥐기
    Crowbar* crowbar;    //쇠지렛대 (무기)
    Transform* mainHand; //주로 쓰는 손 (보통은 오른쪽인)

private:

    void ClipSync(); // 액션이 바뀌었을 때 동작을 재생하는 함수
    void Control();
    void Jump(); // 지금은 좌표격자(높이 0)가 마치 땅인 것처럼 만들어도 OK
                 // 혹은 존재하는 터레인 에디터 혹은 블록 매니저와 연결하거나....

    // 움직임용 변수들...

    ACTION action; // 수행 중인 액션

    // 일단은 예시 (써도 좋고, 수정해도 좋고....)
    float moveSpeed = 0;
    float jumpVelocity = 0;
    float jumpForce = 0.5f;
    float gravityMult = 0.5f;
    bool isJump = false;


    //궤적을 위한 변수
    Transform* startEdge;   //궤적 그리기를 시작할 위치
    Transform* endEdge;     //궤적 그리기를 끝낼 위치

    Trail* trail;           //궤적 클래스에서 만든 인스턴스


    //금기로 가득 찬 임시 코드
    //struct KUNAI
    //{
    //    Model* model; // 쿠나이의 모델
    //    Kunai* main;  // 쿠나이의 메인 클래스
    //};
    //vector<KUNAI> kunais; // 쿠나이 벡터
    //int kunaiIndex = 0;   // 현재 쿠나이의 순번 (다음에 던질 순번)
    //int NextKunai() { return kunaiIndex++ % 5; } // 다음에 던질 순번을 받음과 함께 인덱스+1 하기 위한 함수
};