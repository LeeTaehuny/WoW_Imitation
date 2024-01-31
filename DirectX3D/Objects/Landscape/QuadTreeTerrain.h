#pragma once

class QuadTreeTerrain : public GameObject
{
private:
    const float MAX_HEIGHT = 20.0f;
    const UINT MIN_TRIANGLE = 2048;

    typedef VertexUVNormal VertexType;

    struct Node
    {
        float x, z, size;
        UINT triangleCount = 0;

        Mesh<VertexType>* mesh = nullptr;

        Node* children[4] = {};
    };

public:
    QuadTreeTerrain(wstring heightFile);
    ~QuadTreeTerrain();

    void Render();
    void GUIRender();

private:
    void RenderNode(Node* node);
    void DeleteNode(Node* node);

    void CalcMeshDimensions(UINT vertexCount, float& centerX, float& centerZ, float& size);

    bool IsTriangleContained(UINT index, float x, float z, float size);
    UINT ContainTriangleCount(float x, float z, float size);

    void CreateTreeNode(Node* node, float x, float z, float size);

private:
    UINT width, height;
    UINT triangleCount = 0, drawCount = 0;

    TerrainData* terrainData;
    vector<VertexType> vertices;

    Node* root;
};