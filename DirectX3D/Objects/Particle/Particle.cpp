#include "Framework.h"
#include "Particle.h"

Particle::Particle()
{
    material = new Material; //매티리얼 만들기

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(true);
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL); //나중에 옵션 바꿀 때를 대비
}

Particle::~Particle()
{
    delete material;
    delete vertexBuffer;

    FOR(2) blendState[i];
    FOR(2) depthState[i];
}

void Particle::Render()
{
    // 활성화 되어 있는 한 재생을 계속한다
    if (!isActive) return;

    // 조정된 이미지 출력용 출력상태 설정
    blendState[1]->SetState();
    depthState[1]->SetState();

    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST); //범용 파티클과 마찬가지로 포인트 출력

    //렌더 준비
    material->Set();
    geometryShader->Set();

    DC->Draw(particleCount, 0); // 얼마나, 어디서부터 그릴 것인가 (무엇을 = 위에서 설정해둔 정점버퍼)
    DC->GSSetShader(nullptr, nullptr, 0); //설정은 미리 해두었고 지금은 추가 옵션이 없다

    //출력 상태 원상복구
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void Particle::Play(Vector3 pos)
{
    isActive = true;
    position = pos;
}

void Particle::Stop()
{
    isActive = false;
}
