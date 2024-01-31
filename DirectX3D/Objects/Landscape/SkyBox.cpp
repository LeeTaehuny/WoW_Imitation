#include "Framework.h"

SkyBox::SkyBox(wstring fileName)
{
    //셰이더 적용
    //material->SetShader(L"Basic/Texture.hlsl"); // 기본
    material->SetShader(L"Landscape/Skybox.hlsl");

    skyMap = Texture::Add(fileName);

    FOR(2)
        rasterizerSatate[i] = new RasterizerState();
    rasterizerSatate[1]->FrontCounterClockwise(true); // 여기서 "앞"은 도형의 안을 말한다
                                                      // -> 도형의 안쪽이 반시계 방향 벡터가 된다면?
                                                      // 뒤집힌다 + 렌더 대상에 포함된다 = 안쪽이 눈에 보인다

    FOR(2)
        depthStencilState[i] = new DepthStencilState();
    depthStencilState[1]->DepthEnable(false);         // 사전에 적용된 화소 우선순위가 있었다면 무시한다

    // 위의 래스터1번 상태와 뎁스-스텐실1번 상태를 조합하면?
    // 도형의 안에 있어도 모든 면이 다 보이고, 거기에 씐 텍스처 또한 무조건 다 보인다
    // -> 해당 도형에 하늘 같은 텍스처를 씌우고 크기를 아주 아주 아주 크게 키우고 그 안에 들어가면....
    //    3D 도형은 곧 하늘처럼 보일 것이다
}

SkyBox::~SkyBox()
{
    // 텍스처에서 관리할 스카이맵은 지우지 않아도 좋다

    FOR(2)
        delete rasterizerSatate[i];

    //나중에 스테이트 개수가 서로 달라질 수 있어서 미리 반복문 분리
    FOR(2)
        delete depthStencilState[i];
}

void SkyBox::Render()
{
    skyMap->PSSet(10); // 넉넉하게 슬롯 순위 설정

    //스카이박스용 상태 적용하기
    rasterizerSatate[1]->SetState();
    depthStencilState[1]->SetState();

    Sphere::Render(); // 구체로서 자기 자신을 렌더

    //상태 되돌리기
    rasterizerSatate[0]->SetState();
    depthStencilState[0]->SetState();
}
