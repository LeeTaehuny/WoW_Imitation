#pragma once
class Human : public ModelAnimator
{
private:
    enum class ACTION
    {
        IDLE,
        RUN,
        JUMP
    };

public:
    Human();
    ~Human();

    void Update();
    void Render();
    void GUIRender();

private:
    // ���߿� �ڽ� ��ü�� �ٰų� ���� ���� ����� ����� �ڵ� �߰�
    // �ڽ� ��ü : ����, �賶, ��ź����, �տ� �� ���� ��
    // �������� ��� : �߼Ҹ� üũ�� ���� "�� ��" Ȥ�� ���⸦ ��� ���� "�� ��"

    // �� : �������븦 ����� �����, �տ� ���
    Crowbar* crowbar;    //�������� (����)
    Transform* mainHand; //�ַ� ���� �� (������ ��������)

private:

    void ClipSync(); // �׼��� �ٲ���� �� ������ ����ϴ� �Լ�
    void Control();
    void Jump(); // ������ ��ǥ����(���� 0)�� ��ġ ���� ��ó�� ���� OK
                 // Ȥ�� �����ϴ� �ͷ��� ������ Ȥ�� ��� �Ŵ����� �����ϰų�....

    // �����ӿ� ������...

    ACTION action; // ���� ���� �׼�

    // �ϴ��� ���� (�ᵵ ����, �����ص� ����....)
    float moveSpeed = 0;
    float jumpVelocity = 0;
    float jumpForce = 0.5f;
    float gravityMult = 0.5f;
    bool isJump = false;


    //������ ���� ����
    Transform* startEdge;   //���� �׸��⸦ ������ ��ġ
    Transform* endEdge;     //���� �׸��⸦ ���� ��ġ

    Trail* trail;           //���� Ŭ�������� ���� �ν��Ͻ�


    //�ݱ�� ���� �� �ӽ� �ڵ�
    //struct KUNAI
    //{
    //    Model* model; // ������ ��
    //    Kunai* main;  // ������ ���� Ŭ����
    //};
    //vector<KUNAI> kunais; // ���� ����
    //int kunaiIndex = 0;   // ���� ������ ���� (������ ���� ����)
    //int NextKunai() { return kunaiIndex++ % 5; } // ������ ���� ������ ������ �Բ� �ε���+1 �ϱ� ���� �Լ�
};