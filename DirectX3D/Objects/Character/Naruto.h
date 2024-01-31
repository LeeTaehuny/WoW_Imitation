#pragma once
class Naruto : public ModelAnimator
{
    // ������ : �� �ִϸ����� ���� ���
    //         -> �� ���� ���� ���� (������) �� ���͵� �Ǵϱ�
    //            * ���� �нż� ���� ���ٵ簡 �ϸ� �� ���� �ν��Ͻ� ��� �ʿ�

private:

    //enum class STATE
    enum State
    {
        IDLE,
        RUN_F,
        RUN_B,
        RUN_L,
        RUN_R,
        THROW
        // ���¸��� ���� : fbx�� Ŭ���� (ù ���� �빮��, ������ �ҹ���. ��: "Dying")
        // * �������� ���, �� �ܿ��� punching jump ���� �ٸ� Ŭ���� �ֽ��ϴٸ�...
        //   ���⼱ �ϴ� ���� ���� 6���� �������� Ŭ������ �����ϰڽ��ϴ�.
    };

public:

    Naruto();
    ~Naruto();

    void Update();
    void Render();
    void GUIRender();

private:
    // ������ �޾��� �� �����̱�
    void Control();
    void Move();
    void Rotate();
    void Attack();
    void SetAnimation();

    // ������ ���� ��ȭ�� ���� ���� �ٲٱ�
    void SetState(State state);

    void Throw(); // ������
    void EndThrow(); // ������ ����(1ȸ ����, Ŭ�� ����� ����)�� ������ ��

private:
    Transform* mainHand;
    Model* kunai; // <- �Ŵ��� ���� �ʳ�???
                  //    ���� �̷��� ���� �������� ������ ũ�� 2����
                  //    1. �� ���� ������ �� ������ �ƴ� �� (�տ� ��� �ִٵ簡...)
                  //    2. �� �� ���� ���� �� �ƴϴ���, �ε��� �̸� �ؾ� �� ��

    State curState = IDLE;

    float moveSpeed = 500;
    float rotSpeed = 1;
    float deceleration = 5; // �𼿷����̼� : ����
                            // -> ������ �ϴ� ���ų�, �ٸ� ������ �̵��� ���� �� ��� ������ �ʰ�
                            //    �ӵ��� ����߷��� ���߰� �� �� ����ϴ� ������
                            // �ݴ�� �׼������̼� : ���� (�ӵ��� ������ ������ �޸� �� ���)

    Vector3 velocity;

    //POINT clientCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT / 2 }; // �Ʒ��� 100% ���� �ڵ�
    POINT clientCenterPos = { WIN_WIDTH >> 1, WIN_HEIGHT >> 1 }; // A >> 1 : "A ������ 2"�� ��Ʈ����
                                                                 // 2, 4, 8...Ȥ�� ��Ȯ�� ���� �ʿ� ���� ��
                                                                 // 5, 10 ������ �����⿡ ���� ���� ����
                                                                 // ��Ȯ�� ������ �ʿ��� ���� ���� �� �ȴ�
};

