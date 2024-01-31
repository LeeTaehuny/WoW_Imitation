#include "Framework.h"

ProgressBar::ProgressBar(wstring frontImageFile, wstring backImageFile)
    : Quad(frontImageFile)
{
    // 생성자 호출 시점에서 이 클래스가 갖는 것
    // 1. 쿼드로서의 텍스처 (전면 이미지)
    // 2. 클래스 멤버 텍스처 (후면 이미지)
    // 이 둘을 합치면 진행표시기가(혹은 체력바가) 된다
     
    material->SetShader(L"UI/ProgressBar.hlsl"); // 3D 연산이 빠진, 그림만 계산하는 셰이더

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
