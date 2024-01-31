#include "Framework.h"

KunaiManager::KunaiManager()
{
    kunaiInstancing = new ModelInstancing("Kunai"); // 쿠나이 모델을 공유하는 인스턴싱 생성

    kunaies.reserve(SIZE); // 개수만큼 예약
    FOR(SIZE)
    {
        Transform* transform = kunaiInstancing->Add(); // 인스턴싱에 새 트랜스폼 추가
        transform->SetActive(false); // 일단 비활성화 (안 날아감)
        Kunai* kunai = new Kunai(transform); // 지금 만든 (인스턴싱 속) 트랜스폼을 매개로 한 쿠나이 생성
        kunaies.push_back(kunai); // 쿠나이 벡터에 새로 만든 투사체 메인 클래스도 추가
    }

}

KunaiManager::~KunaiManager()
{
    //모델을 받은 투사체 크래스를 지우고
    for (Kunai* kunai : kunaies)
        delete kunai;

    //먼저 생긴 인스턴싱도 마지막에 지우기
    delete kunaiInstancing;
}

void KunaiManager::Update()
{
    kunaiInstancing->Update(); //모델(과 내부 트랜스폼) 업데이트

    for (Kunai* kunai : kunaies)
        kunai->Update(); //실제 쿠나이 데이터도 업데이트
}

void KunaiManager::Render()
{
    kunaiInstancing->Render();

    for (Kunai* kunai : kunaies)
        kunai->Render();
}

void KunaiManager::Throw(Vector3 pos, Vector3 dir)
{
    for (Kunai* kunai : kunaies)
    {
        //비활성화가 됐던 것부터 차례로 던지기
        if (!kunai->GetTransform()->Active())
        {
            kunai->Throw(pos, dir); // 매개변수 그대로 전달해서 주 멤버 던지기
            return; // 용도를 다 했으니 그대로 종료
        }
    }
}

bool KunaiManager::IsCollision(Collider* collider)
{
    for (Kunai* kunai : kunaies)
    {
        if (kunai->GetCollider()->IsCollision(collider))
        {
            kunai->GetTransform()->SetActive(false); // 이 코드를 비활성화하면 관통효과 가능
            return true;
        }
    }

    return false;
}
