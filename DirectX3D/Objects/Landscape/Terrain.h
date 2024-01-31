#pragma once

class Terrain : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;
    const float MAX_HEIGHT = 20.0f;

public:
    Terrain();
    Terrain(string mapFile);
    ~Terrain();

    void Render();

    //���� �ޱ�
    float GetHeight(const Vector3& pos, Vector3* normal = nullptr);

    //������ ������ó�� ���ǿ� ���߾� ��ǥ�� �޾Ƴ��� ����� �־�� �� ��
    Vector3 Pick(); //��� �Լ�

    Vector2 GetSize() { return Vector2(width, height); }

private:
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();

private:
    UINT width, height;

    Mesh<VertexType>* mesh;

    Texture* heightMap;
    Texture* alphaMap;
    Texture* secondMap;
    Texture* thirdMap;
};