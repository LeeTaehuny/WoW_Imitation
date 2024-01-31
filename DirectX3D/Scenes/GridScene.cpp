#include "Framework.h"
#include "GridScene.h"

GridScene::GridScene()
    : curWidth(MAX_VALUE), curHeight(MAX_VALUE),
    fixWidth(MAX_VALUE), fixHeight(MAX_VALUE)
{
    material = new Material(L"Basic/Grid.hlsl");

    mesh = new Mesh<VertexColor>();
    MakeMesh();
    mesh->CreateMesh();

    worldBuffer = new MatrixBuffer();    
}

GridScene::~GridScene()
{
    delete material;
    delete mesh;
    delete worldBuffer;
}

void GridScene::Update()
{
    bool check = false;
    check |= (curWidth != fixWidth || curHeight != fixHeight);
    check |= (curGridColor != fixGridColor);

    if (!check) return;

    fixWidth = curWidth;
    fixHeight = curHeight;

    fixGridColor = curGridColor;

    MakeMesh();
    mesh->UpdateVertex();
}

void GridScene::PreRender()
{
}

void GridScene::Render()
{
    worldBuffer->SetVS(0);

    material->Set();
    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void GridScene::PostRender()
{
}

void GridScene::GUIRender()
{
    if (ImGui::TreeNode("GridOption"))
    {
        ImGui::DragInt("Width", (int*)&curWidth, 1, 0, MAX_VALUE);
        ImGui::DragInt("Height", (int*)&curHeight, 1, 0, MAX_VALUE);

        ImGui::ColorEdit3("GridColor", (float*)&curGridColor);

        ImGui::TreePop();
    }
}

void GridScene::MakeMesh()
{
    vector<VertexColor>& vertices = mesh->GetVertices();
    vertices.clear();
    //Axis X
    vertices.emplace_back(-MAX_VALUE, 0, 0, 1, 0, 0);
    vertices.emplace_back(+MAX_VALUE, 0, 0, 1, 0, 0);

    //Axis Y
    vertices.emplace_back(0, -MAX_VALUE, 0, 0, 1, 1);
    vertices.emplace_back(0, +MAX_VALUE, 0, 0, 1, 1);

    //Axis Z
    vertices.emplace_back(0, 0, -MAX_VALUE, 0, 0, 1);
    vertices.emplace_back(0, 0, +MAX_VALUE, 0, 0, 1);

    int halfW = curWidth / 2;
    int halfH = curHeight / 2;

    for (int x = -halfW; x <= halfW; x++)
    {
        if (x == 0) continue;

        vertices.emplace_back(x, 0, -halfH, curGridColor.x, curGridColor.y, curGridColor.z);
        vertices.emplace_back(x, 0, +halfH, curGridColor.x, curGridColor.y, curGridColor.z);
    }

    for (int z = -halfH; z <= halfH; z++)
    {
        if (z == 0) continue;

        vertices.emplace_back(-halfW, 0, z, curGridColor.x, curGridColor.y, curGridColor.z);
        vertices.emplace_back(+halfW, 0, z, curGridColor.x, curGridColor.y, curGridColor.z);
    }    
}
