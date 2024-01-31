#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
    forest = new Model("Forest");
    forest->UpdateWorld();

    human = new Human();

    renderTarget = new RenderTarget();
    depthStencil = new DepthStencil();

    quad = new Quad(Vector2(500, 500)); //아무것도 없는 사각형 만들기 (그림이 아니다)
    quad->Pos() = { CENTER_X, CENTER_Y };
    quad->GetMaterial()->SetShader(L"PostEffect/Bloom.hlsl"); // "빛번짐" 효과: 후처리 셰이더 중 하나
    quad->GetMaterial()->SetDiffuseMap(Texture::Add(L"Render", renderTarget->GetSRV()));
                     // 매개변수는 "렌더라는 이름으로 지칭할, 렌더 타겟 객체의 실시간 생성 화면"
    quad->UpdateWorld();

    valueBuffer = new FloatValueBuffer(); //새 소수 연산용 버퍼 생성
    valueBuffer->Get()[0] = 1;
    valueBuffer->Get()[1] = 1;
}

RenderTargetScene::~RenderTargetScene()
{
    delete forest;
    delete human;
    delete renderTarget;
    delete depthStencil;
    delete quad;
    delete valueBuffer;
}

void RenderTargetScene::Update()
{
    human->Update();
}

void RenderTargetScene::PreRender()
{
    renderTarget->Set(depthStencil); // 먼저 설정해둔 뎁스 스텐실 값을 이용해 렌더 타겟 즉시 설정

    forest->Render(); // 타겟으로 설정된 영역(쿼드)에 숲 그리기
    human->Render(); //인간 그리기
    // -> 숲과 인간은 쿼드에 그렸는데 막상 쿼드를 안 그리면 도루묵일 테니 쿼드도 나중에 렌더
}

void RenderTargetScene::Render()
{
    // 월드 렌더
    human->Render();
}

void RenderTargetScene::PostRender()
{
    valueBuffer->SetPS(10);
    quad->Render(); // 쿼드(렌더 타겟의 결과물)를 렌더
}

void RenderTargetScene::GUIRender()
{
    // Threshold : 임계점. 설정한 연산이나 처리가 일어나기 위한 최소(혹은 최대)조건
    //             임계점을 못 넘으면 연산이 아예 수행되지 않음.
    //             게임에서는 방어력이나 공략 조건 등에 응용된다
    ImGui::SliderFloat("Threshold", &valueBuffer->Get()[0], 0, 1);

    // * 위 임계점에 대한 연산값 : 빛번짐 셰이더의 적용 계수
    //   빛에 의한 가시정도(밝은 정도)가 설정된 값 이상일 때 (위 threshold로 설정)
    //   이 옵션에서 설정된 대로 색조가 변화할 것
    ImGui::SliderFloat("Value", &valueBuffer->Get()[1], 0, 10);
}
