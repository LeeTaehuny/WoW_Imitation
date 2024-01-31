#include "Framework.h"

ProgressBar::ProgressBar(wstring frontImageFile, wstring backImageFile)
    : Quad(frontImageFile)
{
    // ������ ȣ�� �������� �� Ŭ������ ���� ��
    // 1. ����μ��� �ؽ�ó (���� �̹���)
    // 2. Ŭ���� ��� �ؽ�ó (�ĸ� �̹���)
    // �� ���� ��ġ�� ����ǥ�ñⰡ(Ȥ�� ü�¹ٰ�) �ȴ�
     
    material->SetShader(L"UI/ProgressBar.hlsl"); // 3D ������ ����, �׸��� ����ϴ� ���̴�

    backImage = Texture::Add(backImageFile);

    valueBuffer = new FloatValueBuffer();
    valueBuffer->Get()[0] = fillAmount;
}

ProgressBar::~ProgressBar()
{
    delete valueBuffer;
}

void ProgressBar::Render()
{
    valueBuffer->SetPS(10);
    backImage->PSSet(10);

    Quad::Render();
}

void ProgressBar::SetAmount(float value)
{
    valueBuffer->Get()[0] = value;
}
