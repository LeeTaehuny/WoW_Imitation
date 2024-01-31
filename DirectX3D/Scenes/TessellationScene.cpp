#include "Framework.h"
#include "TessellationScene.h"

TessellationScene::TessellationScene()
{
    material = new Material(L"TS/Rectangle.hlsl");
    hullShader = Shader::AddHS(L"TS/Rectangle.hlsl");
    domainShader = Shader::AddDS(L"TS/Rectangle.hlsl");

    material->SetDiffuseMap(L"Textures/Etc/Card.png");

    mesh = new Mesh<Vertex>();
    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.emplace_back(-0.9f, -0.9f, 0.0f);
    vertices.emplace_back(-0.9f, +0.9f, 0.0f);
    vertices.emplace_back(+0.9f, -0.9f, 0.0f);
    vertices.emplace_back(+0.9f, +0.9f, 0.0f);
    mesh->CreateMesh();

    edgeBuffer = new FloatValueBuffer();
    edgeBuffer->Get()[0] = 1;
    edgeBuffer->Get()[1] = 1;
    edgeBuffer->Get()[2] = 1;
    edgeBuffer->Get()[3] = 1;

    insideBuffer = new FloatValueBuffer();
    insideBuffer->Get()[0] = 1;
    insideBuffer->Get()[1] = 1;
}

TessellationScene::~TessellationScene()
{
    delete material;
    delete mesh;

    delete edgeBuffer;
    delete insideBuffer;
}

void TessellationScene::Update()
{
}

void TessellationScene::PreRender()
{
}

void TessellationScene::Render()
{
    edgeBuffer->SetHS(10);
    insideBuffer->SetHS(11);

    material->Set();
    hullShader->Set();
    domainShader->Set();

    mesh->Draw(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
}

void TessellationScene::PostRender()
{
}

void TessellationScene::GUIRender()
{
    ImGui::Text("Edge Option");
    ImGui::DragFloat("Edge0", &edgeBuffer->Get()[0]);
    ImGui::DragFloat("Edge1", &edgeBuffer->Get()[1]);
    ImGui::DragFloat("Edge2", &edgeBuffer->Get()[2]);
    ImGui::DragFloat("Edge3", &edgeBuffer->Get()[3]);
    ImGui::DragFloat("Inside1", &insideBuffer->Get()[0]);
    ImGui::DragFloat("Inside2", &insideBuffer->Get()[1]);
}
