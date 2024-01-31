#include "Framework.h"
#include "ShadowScene.h"

ShadowScene::ShadowScene()
{
    forest = new Model("Forest");
    forest->UpdateWorld();
    human = new Human();

    shadow = new Shadow();

    //빛 버퍼 호출
    LightBuffer::Light* light = Environment::Get()->GetLight(0);
    light->type = 1;
    light->pos = { 0, 750, -500 }; // 광원의 위치 (큰 의미는 없을 수 있지만)
    light->range = 2000;           // 빛이 닿는 거리
}

ShadowScene::~ShadowScene()
{
    delete forest;
    delete human;

    delete shadow;

}

void ShadowScene::Update()
{
    human->Update();
}

void ShadowScene::PreRender()
{
    //그림자 클래스를 렌더 타겟 대상으로 지정
    shadow->SetRenderTarget();

    //인간에게 뎁스 스텐실(투과/깊이 버퍼) 적용한 다음
    human->SetShader(L"Light/DepthMap.hlsl");

    //사전에 1회 렌더
    human->Render();
}

void ShadowScene::Render()
{
    shadow->SetRender(); // 그림자 렌더(위 함수에서 연산된 것)를 미리 세팅

    // 그리고 나머지를 다시 렌더 (인간은 여기서 2회째 렌더)
    // 준비된 모델들에게 그림자 여부와 크기를 연산하는 과정(그림자를 가지는 모델용 셰이더) 추가
    forest->SetShader(L"Light/Shadow.hlsl");
    human->SetShader(L"Light/Shadow.hlsl");

    //여기서 진짜 렌더 호출
    forest->Render();
    human->Render();
}

void ShadowScene::PostRender()
{
    shadow->PostRender(); // 호출해서 함수 역할 전달
}

void ShadowScene::GUIRender()
{
    shadow->GUIRender();
}
