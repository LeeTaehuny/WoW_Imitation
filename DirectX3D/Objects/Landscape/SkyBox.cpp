#include "Framework.h"

SkyBox::SkyBox(wstring fileName)
{
    //���̴� ����
    //material->SetShader(L"Basic/Texture.hlsl"); // �⺻
    material->SetShader(L"Landscape/Skybox.hlsl");

    skyMap = Texture::Add(fileName);

    FOR(2)
        rasterizerSatate[i] = new RasterizerState();
    rasterizerSatate[1]->FrontCounterClockwise(true); // ���⼭ "��"�� ������ ���� ���Ѵ�
                                                      // -> ������ ������ �ݽð� ���� ���Ͱ� �ȴٸ�?
                                                      // �������� + ���� ��� ���Եȴ� = ������ ���� ���δ�

    FOR(2)
        depthStencilState[i] = new DepthStencilState();
    depthStencilState[1]->DepthEnable(false);         // ������ ����� ȭ�� �켱������ �־��ٸ� �����Ѵ�

    // ���� ������1�� ���¿� ����-���ٽ�1�� ���¸� �����ϸ�?
    // ������ �ȿ� �־ ��� ���� �� ���̰�, �ű⿡ �� �ؽ�ó ���� ������ �� ���δ�
    // -> �ش� ������ �ϴ� ���� �ؽ�ó�� ����� ũ�⸦ ���� ���� ���� ũ�� Ű��� �� �ȿ� ����....
    //    3D ������ �� �ϴ�ó�� ���� ���̴�
}

SkyBox::~SkyBox()
{
    // �ؽ�ó���� ������ ��ī�̸��� ������ �ʾƵ� ����

    FOR(2)
        delete rasterizerSatate[i];

    //���߿� ������Ʈ ������ ���� �޶��� �� �־ �̸� �ݺ��� �и�
    FOR(2)
        delete depthStencilState[i];
}

void SkyBox::Render()
{
    skyMap->PSSet(10); // �˳��ϰ� ���� ���� ����

    //��ī�̹ڽ��� ���� �����ϱ�
    rasterizerSatate[1]->SetState();
    depthStencilState[1]->SetState();

    Sphere::Render(); // ��ü�μ� �ڱ� �ڽ��� ����

    //���� �ǵ�����
    rasterizerSatate[0]->SetState();
    depthStencilState[0]->SetState();
}
