#pragma once

class ProgressBar : public Quad
{
    // 진행 정도 표시기 : 응용하면 체력바 등에 사용 가능

public:
    ProgressBar(wstring frontImageFile, wstring backImageFile);
    ~ProgressBar();

    void Render();

    //진행 정도 지정 함수
    void SetAmount(float value);

private:
    FloatValueBuffer* valueBuffer;
    Texture* backImage; //배경

    float fillAmount = 1; // 채워진(진행된) 정도 : 초기값은 "전체"
};

