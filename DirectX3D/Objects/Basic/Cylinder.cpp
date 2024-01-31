#include "Framework.h"

Cylinder::Cylinder(float radius, float height, UINT sliceCount)
    : radius(radius), height(height), sliceCount(sliceCount)
{
    tag = "Cylinder";

    mesh = new Mesh<VertexType>();
    MakeMesh();
    MakeNormal();
    MakeTangent();
    mesh->CreateMesh();
}

Cylinder::~Cylinder()
{
    delete mesh;
}

void Cylinder::Render()
{
    SetRender();

    mesh->Draw();
}

void Cylinder::MakeMesh()
{    
    float thetaStep = XM_2PI / sliceCount;    

    vector<VertexType>& vertices = mesh->GetVertices();
    vertices.reserve((sliceCount + 1) * 4);

    VertexType top;
    top.pos = { 0, height * 0.5f, 0 };
    top.uv = { 0.5f, 0.5f };

    //Top
    vertices.push_back(top);   
    for (int i = 0; i <= sliceCount; i++)
    {
        float theta = thetaStep * i;
        
        float x = cos(theta);
        float z = sin(theta);

        VertexType vertex;
        vertex.pos = { x * radius, height * 0.5f, z * radius};
        vertex.uv = { (x + 1) / 2, (z + 1) / 2 };

        vertices.push_back(vertex);        
    }

    VertexType bottom;
    bottom.pos = { 0, -height * 0.5f, 0 };
    bottom.uv = { 0.5f, 0.5f };
    
    //Bottom
    vertices.push_back(bottom);
    for (int i = 0; i <= sliceCount; i++)
    {
        float theta = thetaStep * i;

        float x = cos(theta);
        float z = sin(theta);

        VertexType vertex;
        vertex.pos = { x * radius, -height * 0.5f, z * radius };
        vertex.uv = { (x + 1) / 2, (z + 1) / 2 };

        vertices.push_back(vertex);
    }

    //Side
    for (int i = 0; i <= sliceCount; i++)
    {
        float theta = thetaStep * i;

        float x = cos(theta);
        float z = sin(theta);

        VertexType vertex;
        vertex.pos = { x * radius, -height * 0.5f, z * radius };
        vertex.uv = { (float)i / (float)sliceCount, 1.0f };
        vertices.push_back(vertex);

        vertex.pos = { x * radius, +height * 0.5f, z * radius };
        vertex.uv = { (float)i / (float)sliceCount, 0.0f };
        vertices.push_back(vertex);
    }

    //Á¤Á¡ ÀÎµ¦½º
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve(sliceCount * 6);

    for (UINT i = 0; i < sliceCount; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 2);
        indices.push_back(i + 1);
    }

    UINT bottomIndex = sliceCount + 2;

    for (UINT i = 0; i < sliceCount; i++)
    {
        indices.push_back(bottomIndex);
        indices.push_back(bottomIndex + i + 1);
        indices.push_back(bottomIndex + i + 2);
    }

    UINT sideIndex = (sliceCount + 2) * 2;

    for (UINT i = 0; i < sliceCount; i++)
    {
        indices.push_back(sideIndex + i * 2 + 0);//0
        indices.push_back(sideIndex + i * 2 + 1);//1
        indices.push_back(sideIndex + i * 2 + 2);//2        
                
        indices.push_back(sideIndex + i * 2 + 2);//2
        indices.push_back(sideIndex + i * 2 + 1);//1
        indices.push_back(sideIndex + i * 2 + 3);//3
    }
}

void Cylinder::MakeNormal()
{
    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

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

void Cylinder::MakeTangent()
{
    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; i++)
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 p0 = vertices[index0].pos;
        Vector3 p1 = vertices[index1].pos;
        Vector3 p2 = vertices[index2].pos;

        Vector2 uv0 = vertices[index0].uv;
        Vector2 uv1 = vertices[index1].uv;
        Vector2 uv2 = vertices[index2].uv;

        Vector3 e0 = p1 - p0;
        Vector3 e1 = p2 - p0;

        float u1 = uv1.x - uv0.x;
        float v1 = uv1.y - uv0.y;
        float u2 = uv2.x - uv0.x;
        float v2 = uv2.y - uv0.y;

        float d = 1.0f / (u1 * v2 - v1 * u2);
        Vector3 tangent = d * (e0 * v2 - e1 * v1);

        vertices[index0].tangent += tangent;
        vertices[index1].tangent += tangent;
        vertices[index2].tangent += tangent;
    }
}
