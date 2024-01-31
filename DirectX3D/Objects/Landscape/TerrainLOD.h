#pragma once

class TerrainLOD : public GameObject
{
private:
    typedef VertexUV VertexType;

public:
    TerrainLOD(wstring heightFile);
    ~TerrainLOD();

    void Render();
    void GUIRender();

private:
    void MakeMesh();

private:
    FloatValueBuffer* terrainBuffer;
    FloatValueBuffer* heightBuffer;

    Mesh<VertexType>* mesh;

    HullShader* hullShader;
    DomainShader* domainShader;

    Texture* heightMap;

    UINT cellsPerPatch = 32;
    float cellSpacing = 5;
    Vector2 cellUV;

    UINT width, height;
    UINT patchWidth, patchHeight;
};