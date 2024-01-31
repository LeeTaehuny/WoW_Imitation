#include "Framework.h"

Reflector::Reflector(float width, float height)
    : size(width, height)
{
    SetTag("Reflector");

    material->SetShader(L"Environment/Reflection.hlsl");

    reflection = new Reflection(this);

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->Alpha(true);

    mesh = new Mesh<VertexUV>();
    MakeMesh();
    mesh->CreateMesh();
}

Reflector::~Reflector()
{
    delete mesh;

    delete reflection;

    delete blendState[0];
    delete blendState[1];
}

void Reflector::Update()
{
    reflection->Update();

    UpdateWorld();
}

void Reflector::Render()
{
    SetRender();

    reflection->SetRender();
    blendState[1]->SetState();
    mesh->Draw();
    blendState[0]->SetState();
}

void Reflector::GUIRender()
{
    Transform::GUIRender();
}

void Reflector::SetReflection()
{
    reflection->SetReflection();
}

void Reflector::MakeMesh()
{
    float left = -size.x * 0.5f;
    float right = +size.x * 0.5f;
    float top = +size.y * 0.5f;
    float bottom = -size.y * 0.5f;

    vector<VertexUV>& vertices = mesh->GetVertices();

    vertices.emplace_back(left, 0, top, 0, 0);
    vertices.emplace_back(right, 0, top, 1, 0);
    vertices.emplace_back(left, 0, bottom, 0, 1);
    vertices.emplace_back(right, 0, bottom, 1, 1);

    vector<UINT>& indices = mesh->GetIndices();
    indices = { 0, 1, 2, 2, 1, 3 };
}
