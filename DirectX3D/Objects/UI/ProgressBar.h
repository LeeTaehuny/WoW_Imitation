#pragma once

class ProgressBar : public Quad
{
    // ���� ���� ǥ�ñ� : �����ϸ� ü�¹� � ��� ����

public:
    ProgressBar(wstring frontImageFile, wstring backImageFile);
    ~ProgressBar();

    void Render();

    //���� ���� ���� �Լ�
    void SetAmount(float value);

private:
    FloatValueBuffer* valueBuffer;
    Texture* backImage; //���

    float fillAmount = 1; // ä����(�����) ���� : �ʱⰪ�� "��ü"
};

