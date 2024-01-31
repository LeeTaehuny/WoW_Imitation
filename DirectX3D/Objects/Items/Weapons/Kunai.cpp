#include "Framework.h"
#include "Kunai.h"

Kunai::Kunai(Transform* transform)
    : transform(transform)
{
    // 생성자 단계에서 트랜스폼을 무조건 받아서 생성한다
    // -> 모델은 밖에서 만든다

    transform->Scale() = { 1, 1, 1 }; // 크기 기준 (변화가 필요하면 와서 수정 필요)

    collider = new SphereCollider();
    collider->SetParent(transform); // 충돌체를 트랜스폼에 연결하기

    collider->Scale() = { 1, 1, 1 }; // 충돌체 크기 설정 (변화가 필요하면 와서 수정)
    collider->Pos() = {}; // 기준 위치 설정 (모델과 충돌체 사이에 간극이 있으면 여기서 보정
}

Kunai::~Kunai()
{
    delete collider;
}

void Kunai::Update()
{
    if (!transform->Active()) return; // 활성화가 아니면 연산중지

    time += DELTA;

    if (time > LIFE_SPAN)
        transform->SetActive(false);

    transform->Pos() += direction * speed * DELTA;

    collider->UpdateWorld();
}

void Kunai::Render()
{
    collider->Render();
}

//밖에서 부르기 위한 투척 기능
void Kunai::Throw(Vector3 pos, Vector3 dir)
{
    transform->SetActive(true);

    transform->Pos() = pos;
    direction = dir;

    //transform->Rot().y = atan2(dir.x, dir.z) - XMConvertToRadians(90); //아래 코드와 동일
    transform->Rot().y = atan2(dir.x, dir.z) - XM_PIDIV2;
                       // 나아가는 방향       -    90도
                       // (일반적인 경우) 가로로 만들어질 투사체를 앞뒤로 돌려서 진행할 수 있게

    time = 0; // 진행 시간은 0
}
