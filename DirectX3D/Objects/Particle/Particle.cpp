#include "Framework.h"
#include "Particle.h"

Particle::Particle()
{
    material = new Material; //��Ƽ���� �����

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(true);
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL); //���߿� �ɼ� �ٲ� ���� ���
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
    // Ȱ��ȭ �Ǿ� �ִ� �� ����� ����Ѵ�
    if (!isActive) return;

    // ������ �̹��� ��¿� ��»��� ����
    blendState[1]->SetState();
    depthState[1]->SetState();

    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST); //���� ��ƼŬ�� ���������� ����Ʈ ���

    //���� �غ�
    material->Set();
    geometryShader->Set();

    DC->Draw(particleCount, 0); // �󸶳�, ��𼭺��� �׸� ���ΰ� (������ = ������ �����ص� ��������)
    DC->GSSetShader(nullptr, nullptr, 0); //������ �̸� �صξ��� ������ �߰� �ɼ��� ����

    //��� ���� ���󺹱�
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
