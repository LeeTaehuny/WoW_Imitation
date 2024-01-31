#include "Framework.h"
#include "GBufferScene.h"

GBufferScene::GBufferScene()
{
    gBuffer = new GBuffer();

    forest = new Model("Forest");
    forest->UpdateWorld();
    human = new Human();

    //디퍼드 셰이더를 매티리얼에 적용
    // *디퍼드 셰이더 : 셰이더가 입력을 받았을 때, 연산 결과를 출력으로 그대로 전달하지 않고,
    //                 추가 연산을 연속으로 진행시켜 조건에 따라 다른 결과를 출력하도록 하는 셰이더 기법
    //                 -> 셰이더 연산을 지연시키기 때문에 후처리, 다 된 렌더의 추가 보정 등을 하기에 유리
    //                    화면 화질을 개선하거나, 특수한 효과를 주거나, 화면에서 필요한 정보만 따오거나 하는 데 쓰인다
    //                    렌더 타겟 등에 사용하면 특정한 오브젝트가 아니라, 같은 유형의 오브젝트를
    //                    별도의 UI에 단독으로 출력하거나... 화면의 출력을 특수하게 변형할 수 있게 된다

    // 전체 G버퍼에 디퍼드 셰이더를 적용
    material = new Material(L"Light/Deferred.hlsl"); // <-디퍼드 셰이더
    UINT vertices[4] = { 0, 1, 2, 3 };
    vertexBuffer = new VertexBuffer(vertices, sizeof(UINT), 4);
}

GBufferScene::~GBufferScene()
{
    delete gBuffer;
    delete forest;
    delete human;
    delete material;
    delete vertexBuffer;
}

void GBufferScene::Update()
{
    human->Update();
}

void GBufferScene::PreRender()
{
    //렌더 전 조치

    gBuffer->SetMultiRenderTarget();

    // G버퍼용으로 만들어진 디퍼드 셰이더를 모델에 적용한다
    // * 현재 사용된 셰이더에서 11번을 셰이더 슬롯에 쓰면 디퓨즈맵만,
    //   12는 스페큘러만, 13은 노멀만 출력가능
    forest->SetShader(L"Light/GBuffer.hlsl");
    human->SetShader(L"Light/AnimGBuffer.hlsl");

    forest->Render();
    human->Render();
}

void GBufferScene::Render()
{
    vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    gBuffer->SetSRVs();
    material->Set();

    // 위에 정한 정점버퍼에 의한 결과를 출력
    DC->Draw(4, 0);
}

void GBufferScene::PostRender()
{
    // 프리렌더, 생성자에서 적용했던 후처리용 지연 셰이더가 적용된 결과를
    // 쿼드로 볼 수 있게 된다
    // * 후처리를 통한 그래픽 처리에 걸리는 부하를, G 버퍼의 통합 그래픽 처리가 상충시켜준다
    //   -> 여러 개의 화면, 여러 개의 그래픽 처리가 가능
    gBuffer->PostRender();
}

void GBufferScene::GUIRender()
{
}
