#pragma once

class Trail : public GameObject
{
    // ���� Ŭ���� : ��������Ʈ�� ������ ����� ������ ������, �۵�����̳� ������ �ٸ� Ư�� ��ƼŬ
    // -> �����̳� ���̰� �ִ� ��ü�� ������ ��λ��� ������ �����Ǿ� �������� ������ ��Ÿ���� ����

public:
    Trail(wstring imageFile, Transform* start, Transform* end, UINT width, float speed);
         // �Ű����� : �׸�����, ���� ��ƼŬ(���� ǥ�� ȿ��)�� ������, ����, ������ ũ��, ǥ�� �ӵ�
    ~Trail();

    void Update();
    void Render();

private:
    void CreateMesh();

private:
    Mesh<VertexUV>* mesh; // �̹��� ��¿� �޽�

    Transform* start, * end; //����, �� ��ġ (Ʈ������)

    UINT width; //������ ũ��
    float speed; //����ϴ� �ӵ�

    //��»��� ������ ����
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];
};