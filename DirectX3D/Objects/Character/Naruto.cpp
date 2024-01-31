#include "Framework.h"

Naruto::Naruto()
    : ModelAnimator("Naruto")
{
    // 클라이언트 환경을 통해서 화면상 포인트 위치 재조정
    //ClientToScreen(hWnd, &clientCenterPos);
    //SetCursorPos(clientCenterPos.x, clientCenterPos.y);
    // 앱 시작시 마우스 위치에 의해 시점이 멋대로 돌아가는 것을 줄이기 위해

    // 주 손(여기선 오른손) 설정과 쿠나이 손에 들려주기
    mainHand = new Transform();
    kunai = new Model("Kunai");
    kunai->SetParent(mainHand);
    kunai->SetTag("Kunai");
    kunai->Load();

    // 동작 읽기
    ReadClip("Idle");
    ReadClip("Run"); //RUN_F
    ReadClip("RunBack"); //RUN_B
    ReadClip("RunLeft"); //RUN_L
    ReadClip("RunRight"); //RUN_R
    ReadClip("Throw");

    //던지기(에 해당하는 인덱스의 클립) 동작에 이벤트 설정하기
    GetClip((int)THROW)->SetEvent(bind(&Naruto::Throw, this), 0.7f); // 나루토의 "던지기" 함수를 이벤트에 설정
                                                                     // 시간이 지속식이라면 0.7배 지연으로
    GetClip((int)THROW)->SetEvent(bind(&Naruto::EndThrow, this), 1.0f);
}

Naruto::~Naruto()
{
    delete mainHand;
    delete kunai;
}

void Naruto::Update()
{
    Control(); //조작 실행
    SetAnimation(); //조작에 따른 애니메이션 재생

    mainHand->SetWorld(GetTransformByNode(38)); // 노드의 38번(fbx상 관절나열의 39번째) 트랜스폼이 주로 쓰는 손

    //형태 업데이트 진행
    ModelAnimator::Update();
    kunai->UpdateWorld();
}

void Naruto::Render()
{
    ModelAnimator::Render(); // 모델로서 렌더
    kunai->Render(); // 손에 든 물건도 렌더
}

void Naruto::GUIRender()
{
    Model::GUIRender();
    kunai->GUIRender();
}

void Naruto::Control()
{
    //세부 컨트롤은 각각 따로 작성
    //여기서는 "조작"이라는 이름 아래 총괄만
    
    //Rotate(); // 회전
    Move();   // 이동
    Attack(); // 공격 (현재는 투척)
}

void Naruto::Move()
{
    if (curState == THROW) return; // 던지기 중이면 조작 받지 않음

    bool isMoveZ = false; // 전후 이동 중 아님
    bool isMoveX = false; // 좌우 이동 중 아님

    if (KEY_PRESS('W'))
    {
        velocity.z += DELTA; // 속도(범용변수)에 델타만큼 전후값 주기
        isMoveZ = true; //전후 이동 수행 중
    }

    if (KEY_PRESS('S'))
    {
        velocity.z -= DELTA;
        isMoveZ = true; //전후 이동 수행 중
    }

    if (KEY_PRESS('A'))
    {
        velocity.x -= DELTA;
        isMoveX = true; //좌우 이동 수행 중
    }

    if (KEY_PRESS('D'))
    {
        velocity.x += DELTA;
        isMoveX = true; //좌우 이동 수행 중
    }

    if (velocity.Length() > 1) //속도의 전체 가치가 1을 넘으면 (선으로 표현한 벡터의 길이가 1 초과)
        velocity.Normalize(); //정규화
    // 생각할 거리 : 이 코드가 만약 없으면....?

    if (!isMoveZ) // 전후 이동 중이 아니면
        velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //보간에 의해 감속

    if (!isMoveX) // 좌우이동에 적용
        velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);

    //좌우회전과 행렬계산에 의한 면법선 내기 ( = 정면 구하기)
    Matrix rotY = XMMatrixRotationY(Rot().y);
    Vector3 direction = XMVector3TransformCoord(velocity, rotY); // 현재의 공간이 가지는 "정면"의 실제 벡터 방향

    Pos() += direction * -1 * moveSpeed * DELTA; //"정면" 방향대로 이동
    // * -1 : 캐릭터가 뒤집어져 있어서 (3D fbx나 nif 모델을 직접 사용할 경우 종종 일어나는 일)
    // ** 위 DX 함수 결과 나오는 "정면" : 카메라로부터 멀어지는 방향을 뜻한다
    //                                  경우에 따라 해당 방향이 정면으로 작용하기도 하고, 후면으로 작용하기도 한다
    //                                  (관측자의 이해에 따라 붙는 이름이 다르다)
}

void Naruto::Rotate()
{
    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y); // 마우스가 움직일 때마다 커서 위치를 "중간"으로 재설정

    // 카메라와 캐릭터를 각각 회전 (+추적 카메라로 카메라를 같이 움직이고 있을 것)
    // -> 추적 카메라 설정이 나중에 필요하다!
    Rot().y += delta.x * rotSpeed * DELTA;
    CAM->Rot().x -= delta.y * rotSpeed * DELTA;
}

void Naruto::Attack()
{
    if (curState == THROW) return;

    if (KEY_DOWN(VK_LBUTTON))
    {
        SetState(THROW); // 던지기 상태 시작
    }
}

void Naruto::SetAnimation()
{
    if (curState == THROW) return;

    if (velocity.z > 0.1f) // 전진 속도가 조금이라도 있으면
        SetState(RUN_F);
    else if (velocity.z < -0.1f) // 전후진 상태는 좌우이동 상태보다 우선한다는 코드
        SetState(RUN_B);
    else if (velocity.x < -0.1f) // 좌우 중에선 왼쪽 우선
        SetState(RUN_L);
    else if (velocity.x > 0.1f) // 마지막 오른쪽
        SetState(RUN_R);
    else // 4축 방향 모두 움직임이 (거의) 없음
        SetState(IDLE);

    // *위 조건문에서 0.1 이 더 작은 수로 바뀔수록 동작이 자연스럽고,
    //  동작 전환은 민감하고 경우에 따라 부자연스러울 것 (그 사이에서 자기 균형을 찾아야 함)
}

void Naruto::SetState(State state)
{
    if (state == curState) return;

    curState = state; //상태 갱신 후
    PlayClip(state); // 동작(클립)도 재생
}

void Naruto::Throw()
{
    // 쿠나이 던지기 (매니저 호출)
    KunaiManager::Get()->Throw(kunai->GlobalPos(), Back());
    // 매개변수 1 : "손에 든 무기"의 위치를 기준으로 잡아서 거기서 쿠나이가 날아가도록
    // 매개변수 2 : FBX의 방향과 모델의 방향이 꼭 같지 않을 수 있어서
    //             (나루토는 불러오면 카메라 쪽을 보는 것이 자기의 정면이다)
}

void Naruto::EndThrow()
{
    // 던지기가 끝나고 나면 다시 가만히 있는 동작으로 복귀
    SetState(IDLE);
}