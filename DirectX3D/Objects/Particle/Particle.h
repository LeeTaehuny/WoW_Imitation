#pragma once
class Particle
{
protected:
    UINT MAX_COUNT = 1000;

public:
    Particle();
    ~Particle();

    virtual void Update() {}
    virtual void Render();
    virtual void GUIRender() {}

    virtual void Play(Vector3 pos);
    void Stop();

protected:
    bool isActive = false; //Ȱ��ȭ ���� ���� ���� (�⺻�� : ó������ ��� �� ��)
    UINT particleCount = 0; //������ ��ƼŬ ���� ����
    Vector3 position;

    Material* material; //�ð�ȭ
    VertexBuffer* vertexBuffer; //����(��ġ)

    //������Ʈ�� ���̴�
    GeometryShader* geometryShader;

    BlendState* blendState[2];
    DepthStencilState* depthState[2];
};

