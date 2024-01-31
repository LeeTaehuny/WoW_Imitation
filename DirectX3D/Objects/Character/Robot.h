#pragma once
class Robot
{
private:
    //enum class STATE // <- �� ��� Ŭ������ "STATE" ����� ����
                       //    ���� : Ÿ�ڰ� ������ ���� �ӵ��� (���� ���� ����) ������
                       //  **����** : enum ���� �ߺ��� ��, �ݵ�� �ǵ��� ���� ȣ�� ����
    enum State
    {
        STAND_UP,
        WALK,
        RUN,
        HIT,
        DYING,
        // ���¸��� ���� : fbx�� Ŭ���� (ù ���� �빮��, ������ �ҹ���. ��: "Dying")
    };

public:
    Robot(Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~Robot();

    void Update();
    void Render();
    void PostRender(); //ĳ���Ϳ� ���ӵ� UI�� �ִٸ� ���⼭ �߰�

    void Hit(float amount = 1); // ���ݰ� �ǰ�
    void Spawn(Vector3 pos); // ��ü ���� (�� ��ġ)

    //SphereCollider* GetCollider() { return collider; }
    CapsuleCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

    void SetTarget(Transform* target) { this->target = target; }

private:
    //��� �Լ� (���ο�)

    void SetEvent(int clip, Event event, float timeRatio); //(�� ����ó��) �̺�Ʈ �����ϱ�
    void ExecuteEvent(); // �̺�Ʈ �����ϱ�

    //������ ���� ���� ������ �Լ���
    void EndStandUp();
    void EndHit();
    void EndDying();

    void SetState(State state);

    void Move();
    void UpdateUI();

private:

    Transform* transform;
    //SphereCollider* collider; // �ΰ��� ���Ϳ��� ��ü �浹ü�� ���� ũ��
    CapsuleCollider* collider;   // ĸ�� �ݶ��̴�

    //���� ����ó�� �ۿ��� ����� �Ѱ�����
    ModelAnimatorInstancing* instancing;
    ModelAnimatorInstancing::Motion* motion;

    //���� ��ü���� ������
    Transform* root;    // �ڱ� ���� �ְ�� �޽�(��Ʈ)
    Transform* target;  // �κ��� ǥ�� (�ν� �Ÿ� �����̸� �Ѿư��� �� ���)

    //������ UI
    ProgressBar* hpBar;
    Vector3 barPos; //ü�¹��� ��ġ�� ��ġȭ�� �� (��¥ ��ġ�� ���� �߰�����)

    float moveSpeed = 30;
    float maxHP = 10;
    float curHP = 10;

    Vector3 velocity; // ������ �ᵵ ������ �ƴϾ �Ǵ� ���� ����
                      // ������ ��, �ƴ� �� �� ���� ��� ����
    
    UINT index;
    State curState = STAND_UP; // �ϴ� ������

    vector<map<float, Event>> totalEvents;
    vector<map<float, Event>::iterator> eventIters;
};