#include "Framework.h"

QuadTreeTerrain::QuadTreeTerrain(wstring heightFile)
{
    terrainData = new TerrainData(heightFile);
    width = terrainData->GetSize().x;
    height = terrainData->GetSize().y;

    material->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    vertices = terrainData->GetVertices();
    UINT vertexCount = vertices.size();
    triangleCount = vertexCount / 3;

    float centerX = 0.0f;
    float centerZ = 0.0f;
    float size = 0.0f;

    CalcMeshDimensions(vertexCount, centerX, centerZ, size);

    root = new Node();
    CreateTreeNode(root, centerX, centerZ, size);
}

QuadTreeTerrain::~QuadTreeTerrain()
{
    DeleteNode(root);
    delete root;
}

void QuadTreeTerrain::Render()
{
    drawCount = 0;
    SetRender();
    RenderNode(root);
}

void QuadTreeTerrain::GUIRender()
{
    ImGui::Text("DrawCount : %d", drawCount);
}

void QuadTreeTerrain::RenderNode(Node* node)
{
    Vector3 center(node->x, 0.0f, node->z);
    float radius = node->size * 0.5f;

    if (!CAM->ContainSphere(center, radius))
        return;

    UINT count = 0;
    FOR(4)
    {
        if (node->children[i])
        {
            count++;
            RenderNode(node->children[i]);
        }
    }

    if (count != 0)
        return;

    //Leaf Node
    node->mesh->Draw();
    drawCount += node->triangleCount;
}

void QuadTreeTerrain::DeleteNode(Node* node)
{
    FOR(4)
    {
        if (node->children[i])
        {
            DeleteNode(node->children[i]);
            delete node->children[i];
        }
    }

    delete node->mesh;
}

void QuadTreeTerrain::CalcMeshDimensions(UINT vertexCount, float& centerX, float& centerZ, float& size)
{
    FOR(vertexCount)
    {
        centerX += vertices[i].pos.x;
        centerZ += vertices[i].pos.z;
    }

    centerX /= (float)vertexCount;
    centerZ /= (float)vertexCount;

    float maxX = 0.0f, maxZ = 0.0f;

    FOR(vertexCount)
    {
        float width = abs(vertices[i].pos.x - centerX);
        float depth = abs(vertices[i].pos.z - centerZ);

        if (width > maxX) maxX = width;
        if (depth > maxZ) maxZ = width;
    }

    size = max(maxX, maxZ) * 2.0f;
}

bool QuadTreeTerrain::IsTriangleContained(UINT index, float x, float z, float size)
{
    UINT vertexIndex = index * 3;
    float halfSize = size * 0.5f;

    float x1 = vertices[vertexIndex].pos.x;
    float z1 = vertices[vertexIndex].pos.z;
    vertexIndex++;

    float x2 = vertices[vertexIndex].pos.x;
    float z2 = vertices[vertexIndex].pos.z;
    vertexIndex++;

    float x3 = vertices[vertexIndex].pos.x;
    float z3 = vertices[vertexIndex].pos.z;

    float minX = min(x1, min(x2, x3));
    if (minX > (x + halfSize))
        return false;

    float minZ = min(z1, min(z2, z3));
    if (minZ > (z + halfSize))
        return false;

    float maxX = max(x1, max(x2, x3));
    if (maxX < (x - halfSize))
        return false;

    float maxZ = max(z1, max(z2, z3));
    if (maxZ < (z - halfSize))
        return false;


    return true;
}

UINT QuadTreeTerrain::ContainTriangleCount(float x, float z, float size)
{
    UINT count = 0;

    FOR(triangleCount)
    {
        if (IsTriangleContained(i, x, z, size))
            count++;
    }

    return count;
}

void QuadTreeTerrain::CreateTreeNode(Node* node, float x, float z, float size)
{
    node->x = x;
    node->z = z;
    node->size = size;

    UINT triangles = ContainTriangleCount(x, z, size);

    if (triangles == 0)
        return;

    if (triangles > MIN_TRIANGLE)//쪼개야 하는 노드
    {
        FOR(4)
        {
            float offsetX = (((i % 2) == 0) ? -1.0f : 1.0f) * (size / 4.0f);
            float offsetZ = ((i < 2) ? -1.0f : 1.0f) * (size / 4.0f);

            node->children[i] = new Node();
            CreateTreeNode(node->children[i], x + offsetX, z + offsetZ, size * 0.5f);
        }

        return;
    }

    //Leaf Node 나눌수 없는상황 
    node->triangleCount = triangles;
    UINT vertexCount = triangles * 3;

    node->mesh = new Mesh<VertexType>();
    vector<VertexType>& vertices = node->mesh->GetVertices();
    vertices.resize(vertexCount);

    UINT index = 0, vertexIndex = 0;
    FOR(triangleCount)
    {
        if (IsTriangleContained(i, x, z, size))
        {
            vertexIndex = i * 3;
            vertices[index] = this->vertices[vertexIndex];
            index++;

            vertexIndex++;
            vertices[index] = this->vertices[vertexIndex];
            index++;

            vertexIndex++;
            vertices[index] = this->vertices[vertexIndex];
            index++;
        }
    }

    node->mesh->CreateMesh();
}
