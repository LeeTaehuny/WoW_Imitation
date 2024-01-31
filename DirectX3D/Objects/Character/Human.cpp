#include "Framework.h"
#include "Human.h"

Human::Human() : ModelAnimator("Human") //부모 모델 만들기
{
    //동작 읽기
    ReadClip("Idle", 1);
    ReadClip("Run", 1);
    ReadClip("Jump", 1);

    action = (ACTION)frameBuffer->Get().cur.clip; // 동작이 0번=가만히 있기라서 액션도 가만히 있기

    //무기 생성
    crowbar = new Crowbar();
    crowbar->Load(); // 사전 세팅된 설정이 있는지 보고 있으면 읽기

    //무기를 손에 쥐기
    mainHand = new Transform(); // 트랜스폼이 있다는 것만 정하기
    crowbar->SetParent(mainHand); // 무기 위치 = 내 손

    // 쿠나이 (내재 멤버 데이터) 생성
    //FOR(5)
    //{
    //    KUNAI kunai;
    //    kunai.model = new Model("Kunai");
    //    kunai.model->Scale() *= 10; // 휴먼은 큰데 쿠나이는 너무 작아서
    //    kunai.main = new Kunai(kunai.model); //메인 데이터에 모델의 트랜스폼을 넣어서 생성
    //    kunai.main->GetTransform()->SetActive(false); // 일단 비활성화
    //    kunais.push_back(kunai); //벡터에 추가
    //}


    // 쿠나이 (매니저) 생성
    KunaiManager::Get(); // 필수는 아닌데 해두면 플레이 도중 렉 유발을 줄일 수 있음

    //-----------------------

    // 궤적과 궤적용 데이터 생성

    startEdge = new Transform();
    endEdge = new Transform();
    trail = new Trail(L"Textures/Effect/Trail.png", startEdge, endEdge, 10, 10.0f);
}

Human::~Human()
{
    delete crowbar;
    delete mainHand; // <- 이렇게 지워도 되는 이유 : 포인터는 지워도 데이터가 날아가진 않는다
                     // 단지 그 자리에 덮어씌워질 가능성이 생길 뿐
                     // 그리고 이 "손"의 진짜 데이터는 아직 원본이 그 자리에 남아 있다

    delete trail;
    delete startEdge;
    delete endEdge;

    //FOR(5)
    //{
    //    delete kunais[i].main;
    //    delete kunais[i].model;
    //}   
}

void Human::Update()
{
    ClipSync();
    Control();
    Jump();

    // 업데이트에서 중요한 것 : 1. 내 손은 무엇인가 (쇠지렛대보다 먼저 수행해야 함)
    //                        2. 그리고 내 손은 어디 있는가 (그래야 거기에 무기가 있을 테니까)

    mainHand->SetWorld(GetTransformByNode(51)); //트랜스폼의 공간 할당하기
    // GetTransformByNode : 모델 애니메이터에서 만들었던 "노드에 할당된 트랜스폼 받아오기"
    // 매개변수 51 : Human.fbx 기준 오른손이 있었던 노드의 순서

    crowbar->Update();

    //궤적 준비
    startEdge->Pos() = crowbar->GlobalPos() + crowbar->Up() * 200.0f; // 마지막 항의 샘플값
    endEdge->Pos() = crowbar->GlobalPos() - crowbar->Up() * 200.0f;   // = 100.0f
    // 시작 위치와 끝 위치를 쇠지렛대 위치와 크기를 기준으로 도출
    // 샘플에서 쓰인 100.0f : 쇠지렛대 모델에서 추측한 모델의 크기
    // (모델이 바뀌거나 크기가 안 맞으면 수정)

    //준비한 끄트머리 트랜스폼 업데이트
    startEdge->UpdateWorld();
    endEdge->UpdateWorld();

    ModelAnimator::Update(); //원본으로서의 업데이트 또한 수행
                             //클래스명이 없으면 재귀함수가 돼서 문제 발생

    trail->Update(); //모델 + 쇠지렛대 업데이트 후 궤적도 업데이트

    //임시 업데이트
    //FOR(5) kunais[i].model->UpdateWorld();
    //FOR(5) kunais[i].main->Update();

    // 쿠나이 (매니저) 업데이트
    KunaiManager::Get()->Update();
}

void Human::Render()
{
    crowbar->Render();

    ModelAnimator::Render();

    trail->Render();

    //임시 렌더
    //FOR(5) kunais[i].main->Render(); // <-렌더는 메인 클래스 안에 모델 렌더가 포함

    // 쿠나이(매니저) 렌더
    KunaiManager::Get()->Render();
}

void Human::GUIRender()
{
    crowbar->GUIRender();
    ModelAnimator::GUIRender();

    //임시 ImGui
    //FOR(5) kunais[i].main->GetTransform()->GUIRender();
}

void Human::ClipSync()
{
    // 재생 중인 동작이 설정된 액션과 달라지면
    if ((ACTION)frameBuffer->Get().cur.clip != action)
    {
        // 행동에 맞는 동작 재생
        PlayClip((int)action);
    }
}

void Human::Control()
{
    if (!isJump)
    {
        if (KEY_PRESS('W'))
        {
            action = ACTION::RUN;
        }

        if (KEY_DOWN(VK_SPACE))
        {
            action = ACTION::JUMP;
            jumpVelocity = jumpForce;
            isJump = true;
        }

        if (KEY_UP('W'))
        {
            action = ACTION::IDLE;
        }

        if (KEY_DOWN(VK_RETURN))
        {
            //kunais[NextKunai()].main->Throw(Pos(), Forward());

            KunaiManager::Get()->Throw(Pos(), Forward());
        }
    }
}

void Human::Jump()
{
    jumpVelocity -= 9.8f * gravityMult * DELTA;
    Pos().y += jumpVelocity;

    if (Pos().y > 0)
    {
        if (action != ACTION::JUMP) action = ACTION::JUMP;
        isJump = true;
    }

    if (Pos().y < 0)
    {
        Pos().y = 0;
        jumpVelocity = 0;
        if (action == ACTION::JUMP) action = ACTION::IDLE;
        isJump = false;
    }
}
