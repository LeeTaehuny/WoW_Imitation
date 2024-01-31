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

    //높이 받기
    float GetHeight(const Vector3& pos, Vector3* normal = nullptr);

    //지형도 에디터처럼 조건에 맞추어 좌표를 받아내는 기능이 있어야 할 것
    Vector3 Pick(); //찍기 함수

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