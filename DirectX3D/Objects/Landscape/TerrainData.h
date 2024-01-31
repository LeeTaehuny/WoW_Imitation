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
    vector<VertexType> alignedVertices;
    vector<UINT> indices;

    UINT width, height;

    Texture* heightMap;
};