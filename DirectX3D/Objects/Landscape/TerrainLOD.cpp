#include "Framework.h"

TerrainLOD::TerrainLOD(wstring heightFile)
{
    material->SetShader(L"TS/TerrainLOD.hlsl");
    material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    hullShader = Shader::AddHS(L"TS/TerrainLOD.hlsl");
    domainShader = Shader::AddDS(L"TS/TerrainLOD.hlsl");

    heightMap = Texture::Add(heightFile);

    terrainBuffer = new FloatValueBuffer();
    heightBuffer = new FloatValueBuffer();

    terrainBuffer->Get()[0] = 1.0f;
    terrainBuffer->Get()[1] = 1000.0f;
    terrainBuffer->Get()[2] = 1.0f;
    terrainBuffer->Get()[3] = 64.0f;

    heightBuffer->Get()[0] = 20.0f;

    mesh = new Mesh<VertexType>();
    MakeMesh();
    mesh->CreateMesh();
}

TerrainLOD::~TerrainLOD()
{
    delete mesh;

    delete terrainBuffer;
    delete heightBuffer;
}

void TerrainLOD::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);

    terrainBuffer->SetHS(10);
    heightBuffer->SetDS(10);

    heightMap->DSSet();

    material->Set();
    hullShader->Set();
    domainShader->Set();

    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

    DC->HSSetShader(nullptr, nullptr, 0);
    DC->DSSetShader(nullptr, nullptr, 0);
}

void TerrainLOD::GUIRender()
{
    ImGui::Text("TerrainLOD Option");
    ImGui::DragFloat("MinDistance", &terrainBuffer->Get()[0]);
    ImGui::DragFloat("MaxDistance", &terrainBuffer->Get()[1]);
    ImGui::DragFloat("MinQuality", &terrainBuffer->Get()[2]);
    ImGui::DragFloat("MaxQuality", &terrainBuffer->Get()[3]);
    ImGui::DragFloat("HeightScale", &heightBuffer->Get()[0]);
}

void TerrainLOD::MakeMesh()
{
    width = heightMap->GetSize().x;
    height = heightMap->GetSize().y;

    cellUV = { 1.0f / width, 1.0f / height };

    patchWidth = ((width - 1) / cellsPerPatch) + 1;
    patchHeight = ((height - 1) / cellsPerPatch) + 1;

    //정점 데이터
    vector<VertexType>& vertices = mesh->GetVertices();
    vertices.resize(patchWidth * patchHeight);

    float halfWidth = width * cellSpacing * 0.5f;
    float halfHeight = height * cellSpacing * 0.5f;

    float tempWidth = width * cellSpacing / patchWidth;
    float tempHeight = height * cellSpacing / patchHeight;

    float du = 1.0f / patchWidth;
    float dv = 1.0f / patchHeight;

    for (UINT z = 0; z < patchHeight; z++)
    {
        float tempZ = halfHeight - z * tempHeight;
        for (UINT x = 0; x < patchWidth; x++)
        {
            float tempX = -halfHeight + x * tempWidth;

            UINT index = patchWidth * z + x;
            vertices[index].pos = { tempX, 0.0f, tempZ };
            vertices[index].uv = { x * du, z * dv };
        }
    }

    //정점 인덱스
    vector<UINT>& indices = mesh->GetIndices();
    indices.reserve((patchWidth - 1) * (patchHeight - 1) * 4);

    for (UINT z = 0; z < patchHeight - 1; z++)
    {
        for (UINT x = 0; x < patchWidth - 1; x++)
        {
            indices.push_back(patchWidth * z + x);
            indices.push_back(patchWidth * z + x + 1);
            indices.push_back(patchWidth * (z + 1) + x);
            indices.push_back(patchWidth * (z + 1) + x + 1);
        }
    }
}

