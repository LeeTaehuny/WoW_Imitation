#include "Framework.h"

Robot::Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index)
    : transform(transform) // 트랜스폼
    , instancing(instancing) // 인스턴싱 데이터
    , index(index)           // 인스턴싱 내 순번
{
    root = new Transform(); // 아직 모델을 다 받지는 않음

    //모델에 의해서 root가 바뀌기 전에 충돌체 생성
    collider = new CapsuleCollider(30, 100); // 반지름, 높이 순으로 매개변수 적용
    collider->SetParent(root); //위에서 만든 루트를 여기에 매개변수로 적용
    collider->Rot().z = XM_PIDIV2 - 0.2f; //약간 구부정한 로봇의 모양을 맞춰주기 (모델별 옵션)
    collider->Pos() = { -15.0f, 10.0f, 0.0f }; //로봇 모델의 재현 위치와 충돌체 맞춰주기 (모델에 따라 다른 옵션)

    //동작
    motion = instancing->GetMotion(index);
    totalEvents.resize(instancing->GetClipSize());
    eventIters.resize(instancing->GetClipSize());

    //이벤트 설정 (현재 만들어진 것만)
    SetEvent(STAND_UP, bind(&Robot::EndStandUp, this), 0.7f);
    SetEvent(HIT, bind(&Robot::EndHit, this), 0.9f);
    SetEvent(DYING, bind(&Robot::EndDying, this),  1);

    FOR(totalEvents.size())
    {
        eventIters[i] = totalEvents[i].begin();
    }

    velocity = Vector3(); // 속력 벡터 초기화

    //캐릭터용 UI 추가
    hpBar = new ProgressBar(
        L"Textures/UI/hp_bar.png",
        L"Textures/UI/hp_bar_BG.png"
    );
}

Robot::~Robot()
{
    delete collider;
    delete root;
    delete hpBar;
}

void Robot::Update()
{
    // 활성화 중에만 로봇 알고리즘 업데이트
    if (!transform->Active()) return;

    //업데이트에서 속력 벡터를 계산해야 한다면 이쪽의 코드를 활성화
    // 그리고 Move() 속 코드를 삭제할 것
    velocity = target->GlobalPos() - transform->GlobalPos();

    //업데이트가 필요한 함수들
    Move();  // 이동
    ExecuteEvent(); // 이벤트 실행
    UpdateUI(); //UI 업데이트

    root->SetWorld(instancing->GetTransformByNode(index, 3)); //Robot 모델은 3번이 루트 노드
    collider->UpdateWorld(); // 충돌체 업데이트
}

void Robot::Render()
{
    //실제 모델 렌더(진짜 렌더) : 인스턴싱에서 해줄듯
    collider->Render(); //충돌체 렌더

}

void Robot::PostRender()
{
    //UI 추가
    hpBar->Render();
}

void Robot::Hit(float amount)
{
    // 공격을 하거나 받을 때 쓰는 함수
    // 일단 지금은 받는 용도로 (쓴다면 추가 매개변수가 더 있어야 할 것)

    //HP를 지정받은 만큼 깎기
    curHP = curHP - amount;
    hpBar->SetAmount(curHP / maxHP); // 체력 비율에 따라 체력바 수치 조정

    if (curHP <= 0)
    {
        SetState(DYING); // 체력이 0 이하면 죽고 종료
        return;
    }

    // 여기까지 오면 맞았고, 아직 살아는 있다
    curState = HIT;
    instancing->PlayClip(index, HIT); // 모델 인스턴싱에서 "이" 로봇의 맞은 모션 재생
    eventIters[HIT] = totalEvents[HIT].begin(); // 반복자 재설정

    // *참고 : 공격에도 쓴다면 위 함수를 A 연산으로 (조건문에 따라) 이 아래에 공격 코드를 추가
    //         ...혹은 원한다면 별도의 함수 작성해서 호출해도 OK
}

void Robot::Spawn(Vector3 pos)
{
    transform->SetActive(true); //트랜스폼 활성화
    collider->SetActive(true);

    SetState(WALK); // 일단 앞으로

    //체력 리셋
    curHP = maxHP;

    transform->Pos() = pos; //지정된 위치로
}

void Robot::SetEvent(int clip, Event event, float timeRatio)
{
    if (totalEvents[clip].count(timeRatio) > 0) // 한 동작에, 같은 시점으로 지정된 이벤트가 여럿이면
        return; //종료

    totalEvents[clip][timeRatio] = event; // 이벤트 세팅
}

void Robot::ExecuteEvent()
{
    // 모델 애니메이터에 있던 이벤트 실행 함수와 비슷하다
    // 한쪽 함수를 보다가 헷갈리면 다른 쪽을 같이 보면 된다

    int index = curState; // 현재 상태를 임시 인덱스로 받기

    if (totalEvents[index].empty()) return; //현재 지정된 이벤트가 0개면 종료
    if (eventIters[index] == totalEvents[index].end()) return; // 이벤트 반복자가 끝이면 = 이벤트 끝났으면 종료

    float ratio = motion->runningTime / motion->duration; // (시간)비율 = 재생시간 / 전체 재생시간

    if (eventIters[index]->first > ratio) return; // 아직 시간이 다 안 찼으면 종료

    //여기까지 오면 이벤트가 실행되어야 할 준비가 끝난 것 (이벤트 있음, 시간 다 됐음)
    eventIters[index]->second(); // 이벤트를 호출(실행)
    eventIters[index]++;         // 반복자 한 차례 뒤로 넘기기
                    //(단독 이벤트라면 end(), 다음 시간에 의한 이벤트가 또 있다면 2번째, 3번째 등으로...)
}

//구체적인 이벤트들
void Robot::EndStandUp()
{
    //일어나는 동작을 수행을 시작했고, 일어나는 동작이 또 다 끝난 상황
    // -> 걷기 시작

    collider->SetActive(true); // 활성화가 안 되었다면 시키기
    SetState(WALK);
}

void Robot::EndHit()
{
    // 한 대 맞은 것
    // -> 맞았고 아직 살아도 있는 것 (죽었다면 Hit 함수 내에서 죽는 코드를 실행했을 테니까)

    SetState(WALK); // 계속 이동 (Move 함수에 의해 어차피 속력벡터 계산과 걷기/달리기 구분은 알아서 한다)
}

void Robot::EndDying()
{
    // 죽었으니까 없어지면 된다
    // 시간을 지연시키고 싶으면 : 충돌체만 없앤 다음 약간 시간을 더 주고 다른 함수로 트랜스폼까지 없애주면 된다
    transform->SetActive(false);
    collider->SetActive(false);
}

void Robot::SetState(State state)
{
    if (state == curState) return;

    curState = state; //상태 지정
    instancing->PlayClip(index, state); // 동작 수행
    eventIters[state] = totalEvents[state].begin(); // 반복자 리셋
}

void Robot::Move()
{
    //로봇의 이동 알고리즘

    if (curState == STAND_UP) return; // 상태가 "가만히 있기"면 종료
    if (curState == HIT) return; // 상태가 "맞는 중"이어도 종료
    if (curState == DYING) return; // 상태가 "죽었거나 죽는 중"이어도 종료
    if (velocity.Length() < 10) return; // 속도에 영향을 줘야 할 중간변수(여기서는 "대상과의 거리")가 너무 적어도 종료

    // 여기까지 오면 로봇이 멈춰야 할 이유가 더 남지 않는다
    // -> 이동 시작

    // 속력의 원형 데이터 도출 (이동에 쓰이지만 좀 더 범용이 되면 업데이트로 이 코드 옮길 것)
    //                       (....혹은 이 코드가 이 함수 안에 있음으로 인해 위쪽 if문과 충돌 나는 경우도 포함)
    //velocity = target->GlobalPos() - transform->GlobalPos(); //표적과 자신의 거리관계에 따라 속력 벡터

    // 표적에게 가까이 가기 전에는 천천히 다가가서, 거리가 좁혀지면 달려들기
    if (velocity.Length() < 1000) //속력벡터의 길이(=표적과의 실제 거리)가 지정된 수 미만이면
    {
        moveSpeed = 100; //빠른 이동 시작
        SetState(RUN); //동작 : 달리기
    }
    else // 거리가 너무 멀면
    {
        moveSpeed = 50;
        SetState(WALK);
    }

    // 위치 갱신 및 회전 계산하기
    transform->Pos() += velocity.GetNormalized() * moveSpeed * DELTA;
    transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI; // 속력벡터에 의한 회전값 + 모델에 의한 보정계수
}

void Robot::UpdateUI()
{
    barPos = transform->Pos() + Vector3(0, 180, 0); //Y 180 : 액터 크기 (모델이 바뀌면 이쪽도 수정)

    hpBar->Pos() = CAM->WorldToScreen(barPos); // 월드상의 개체를 2D 화면으로 투사
                                               // UI의 캔버싱이라고 한다
    float scale = 100 / velocity.Length(); // 표적과의 거리에 따라 그림 크기가 달라지게

    scale = Clamp(0.1f, 1.0f, scale); // 최대 최소 범위를 넘지 않게

    hpBar->Scale() = { scale, scale, scale };

    hpBar->UpdateWorld(); // 정점 업데이트
}
