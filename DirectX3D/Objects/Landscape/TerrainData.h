#pragma once

class TerrainData
{
private:
    const float MAX_HEIGHT = 20.0f;
    typedef VertexUVNormal VertexType;

public:
    TerrainData(wstring heightFile);
    ~TerrainData() = default;

    vector<VertexType> GetVertices() { return alignedVertices; }
    Vector2 GetSize() { return Vector2(width, height); }

private:
    void MakeMesh();
    void MakeNormal();
    void AlignVertexData();

private:
    vector<VertexType> vertices;
    vector<VertexType> alignedVertices; // 각 정점에 인접한 정점 정보
    vector<UINT> indices;   // 정점 목록에서 출력할 정점의 집합을 규정한 것
    // 정점의 인덱스와 정점의 인접지 차이
    // 인덱스는 해당정점 그 자체의 순번을 나타냄
    // 목록이 모이면 순서를 통해 인접정보를 간접적으로 알수는 있음(직접 알려면 다시 계산)
    // 인접지 정보는 정점에서 인접한 정점들의 실제 정보를 가짐
    // 주변정보를 빠르게 참조 가능한데 메모리를 소모하고 자체적으로 순번목록을 유추불가
    // 그래서 랜더에 쓸 수 없음

    UINT width, height;

    Texture* heightMap;
};