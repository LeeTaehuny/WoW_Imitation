#include "Framework.h"

TerrainData::TerrainData(wstring heightFile)
{
    heightMap = Texture::Add(heightFile);

    MakeMesh();
    MakeNormal();
    AlignVertexData();
}

void TerrainData::MakeMesh()
{
    width = (UINT)heightMap->GetSize().x;
    height = (UINT)heightMap->GetSize().y;

    vector<Float4> pixels;
    heightMap->ReadPixels(pixels);

    //정점 데이터
    vertices.reserve(width * height);
    for (UINT z = 0; z < height; z++)
    {
        for (UINT x = 0; x < width; x++)
        {
            VertexType vertex;
            vertex.pos = { (float)x, 0.0f, (float)(height - z - 1) };
            vertex.uv.x = x / (float)(width - 1);
            vertex.uv.y = z / (float)(height - 1);

            UINT index = width * z + x;
            vertex.pos.y = pixels[index].x * MAX_HEIGHT;

            vertices.push_back(vertex);
        }
    }

    indices.reserve((width - 1) * (height - 1) * 6);

    for (UINT z = 0; z < height - 1; z++)
    {
        for (UINT x = 0; x < width - 1; x++)
        {
            indices.push_back(width * z + x);//0
            indices.push_back(width * z + x + 1);//1
            indices.push_back(width * (z + 1) + x);//2            

            indices.push_back(width * (z + 1) + x);//2
            indices.push_back(width * z + x + 1);//1            
            indices.push_back(width * (z + 1) + x + 1);//3
        }
    }
}

void TerrainData::MakeNormal()
{
    for (UINT i = 0; i < indices.size() / 3; i++)
    {
        UINT index0 = indices[i * 3 + 0]; 
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 v0 = vertices[index0].pos;
        Vector3 v1 = vertices[index1].pos;
        Vector3 v2 = vertices[index2].pos;

        Vector3 e0 = v1 - v0;
        Vector3 e1 = v2 - v0;

        Vector3 normal = Cross(e0, e1).GetNormalized();

        vertices[index0].normal = normal + vertices[index0].normal;
        vertices[index1].normal = normal + vertices[index1].normal;
        vertices[index2].normal = normal + vertices[index2].normal;
    }
}

void TerrainData::AlignVertexData()
{
    alignedVertices.reserve(indices.size());

    for (UINT z = 0; z < height - 1; z++)
    {
        for (UINT x = 0; x < width - 1; x++)
        {
            UINT index0 = width * z + x; // 자신
            UINT index1 = width * z + x + 1; // 우
            UINT index2 = width * (z + 1) + x; // 하
            UINT index3 = width * (z + 1) + x + 1; //대각

            
            alignedVertices.push_back(vertices[index0]);
            alignedVertices.push_back(vertices[index1]);
            alignedVertices.push_back(vertices[index2]);

            alignedVertices.push_back(vertices[index2]);
            alignedVertices.push_back(vertices[index1]);
            alignedVertices.push_back(vertices[index3]);
        }
    }
}
