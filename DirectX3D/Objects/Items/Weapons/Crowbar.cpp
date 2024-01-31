#include "Framework.h"
#include "Crowbar.h"

Crowbar::Crowbar() : Model("crowbar")
{
    SetTag("Crowbar");

    //충돌체 지정하기
    collider = new BoxCollider();
    collider->SetTag("CrowbarCollider"); // 태그 정하기 (부모와 같은 키워드를 공유하면 좋다)
    collider->SetParent(this);           // 부모 정하기
    collider->Load();                    // 트랜스폼 정보 로드하기 (파일이 있다면)
}

Crowbar::~Crowbar()
{
    delete collider;
}

void Crowbar::Update()
{
    UpdateWorld(); // 자기 업데이트
    collider->UpdateWorld(); //충돌체도 업데이트
}

void Crowbar::Render()
{
    Model::Render(); // 자기 렌더
    collider->Render(); // 충돌체 렌더
}

void Crowbar::GUIRender()
{
    Model::GUIRender();
    collider->GUIRender();
}
