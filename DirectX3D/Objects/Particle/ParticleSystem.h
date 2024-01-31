#pragma once
class ParticleSystem
{
    // ��ƼŬ ��ü�� ������ ������ ����ϴ� ���� Ŭ����
    // -> �Ϲ����� ��ƼŬ�� �� Ŭ������ ������
    //    ���� Ư���� ��ƼŬ�� �ʿ��ϸ� ���� �ش� Ŭ������ �� �ۼ�

    // * ��ƼŬ : ����� ����, ����. ���α׷��ֿ����� �ܹ������� �����Ǵ� 2D Ȥ�� 3D �̹���
    //           ���� ���ӽð��� ª�ų�, �ܱⰣ�� ���� ��ü�� �����Ǿ�� �ϴ� ��찡 ���Ƽ�
    //           �Ϲ����� 2D �̹���(����, ���ǵ�Ʈ��) ����� ������ ���� �ٸ���

private:
    //��ƼŬ�� �ʿ��� �����͵�

    //�� ȿ���� ��� ����Ǵ°�? = ���(����) �ʿ�
    struct InstanceData
    {
        Matrix transform = XMMatrixIdentity(); // �Ϲ� ��ü Ŭ������ Ʈ�������� ����
    };

    //��ƼŬ ��ü�� ���� (�پ���) Ư�� �ɼ�
    struct ParticleData
    {
        bool isLoop = false; // ���ѹݺ� ����
        bool isAdditive = true; // �̹����� ȭ�Ұ� ����(���) ȭ�ҿ� �������°�? = ���� ���� ȿ���� ������ ���ΰ�
        bool isBillboard = true; // ī�޶� ���⿡ ������� ������ ���� ������ �̹����� ���� ���ΰ�?
        UINT count = 100; // ī��Ʈ �ɼ� : ���ÿ� ���� ������ ��, ��������Ʈ ��... �� �پ��� ��Ȳ���� ���δ�
        float duration = 1.0f; //����Ʈ ���ӽð�
        Vector3 minVelocity = { -1, -1, -1 }; //�ּ� �ӷ±���(+����)
        Vector3 maxVelocity = { +1, +1, +1 }; //�ִ� �ӷ±���(+����)
        Vector3 minAcceleration; //�ּ� ���ӷ�(�ӵ���ȭ��)
        Vector3 maxAcceleration; //�ִ� ���ӷ�(�ӵ���ȭ��)
        Vector3 minStartScale = { 1, 1, 1 }; //������ �ּ� ũ��
        Vector3 maxStartScale = { 1, 1, 1 }; //������ �ִ� ũ��
        Vector3 minEndScale = { 1, 1, 1 }; //��� ����� �ּ� ũ��
        Vector3 maxEndScale = { 1, 1, 1 }; //��� ����� �ִ� ũ��
        float minSpeed = 1.0f; // �ּ� �ӷ� (���� ������)
        float maxSpeed = 3.0f; // �ִ� �ӷ� (���� ������)
        float minAngularVelocity = -10.0f; // �ּ� ���� ������ (�ִٸ�)
        float maxAngularVelocity = +10.0f; // �ִ� ���� ������ (�ִٸ�)
        float minStartTime = 0.0f; //�ּ� ���� ���� �ð�
        float maxStartTime = 0.0f; //�ִ� ���� ���� �ð�
        Float4 startColor = { 1, 1, 1, 1 }; //���۽� ���� ����
        Float4 endColor = { 1, 1, 1, 1 }; //��� ����� ���� ����
        // �ٸ� ��������, ���̴� ����, �����׸� ���� ���� ������� ���� �� �ʿ���
        // �ּ����� ��ƼŬ �ɼ��� ���⼭ ���� ����
    };

    //��ƼŬ�� ����
    struct ParticleInfo
    {
        Transform transform;
        Vector3 velocity;
        Vector3 acceleration;
        Vector3 startScale;
        Vector3 endScale;

        float speed = 1.0f;
        float angularVelocity = 0.0f;
        float startTime = 0.0f;

        // ��ƼŬ�� ���� ����ü : �Ϲ� ����, Ȥ�� ���� ������ ��´�
        // �Ϲ� ������ �� : ��ƼŬ�� ��� ����, �����ڰ� ���� ����� ������ �ۼ�, �ܺ� ���� ����
        // ���� ������ �� : ������ ��ƼŬ�� ������ ���������� ���´� (�� ����ü�� ������ ����)
        //                 -> ȣ���ϸ� ���� ������� n��° ���� ����Ʈ�� �ɼ��� Ȯ�� ����
    };

public:
    ParticleSystem(string file); //�ؽ�ó ���̴� ������ �� ���� ���� ��ƼŬ�� ����̹Ƿ�
    ParticleSystem(wstring file);
    ~ParticleSystem();

    void Update();
    void Render();
    void GUIRender();

    void Play(Vector3 pos, Vector3 rot = Vector3()); // ��ġ�� �ʼ�, ȸ���� �ɼ�, �⺻���� {0,0,0}
                                                     // (->�⺻ ����� �������� �״ϱ�...)
    void Stop();

    bool IsActive() { return quad->Active(); } //�� ��ƼŬ�� Ȱ��ȭ ���ΰ�? -> �簢������ ���� ����

private:
    void UpdatePhysical(); //��ü�� ������Ʈ�ϴ� �Լ�
    void UpdateColor();    //������ ������Ʈ�ϴ� �Լ�
    void Init();           //��� ����

    void LoadData(string file); //������ ������ �ؽ�Ʈ ���� ������ �ִ� ���
    void LoadData(wstring file); //�ؽ�ó�� ������ ����� ���

private:
    Quad* quad; //�̹����� ���� �簢��

    vector<InstanceData> instances; //������� Ʈ������(���� �����)��
    vector<ParticleInfo> particleInfos; //��ƼŬ���� ���� (���� ���� ���)

    VertexBuffer* instanceBuffer; //�ν��Ͻ��� �����ϴ� ������ ����

    ParticleData data; //�� ��ƼŬ�� ���� �ɼ�

    float lifeSpan = 0.0f;          // ��ƼŬ�� �����ֱ�
    UINT drawCount = 0;             // ��� ��û Ƚ��
    UINT particleCount = 100;       // ��ƼŬ�� ���� ī��Ʈ

    //�̹��� ����� ���� ������Ʈ
    BlendState* blendState[2];
    DepthStencilState* depthState[2];
};

