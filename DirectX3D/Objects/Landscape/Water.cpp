#include "Framework.h"

Water::Water(wstring normalFile, float width, float height)
    : size(width, height)
{
    SetTag("Water");

    material->SetShader(L"Environment/Water.hlsl");

    reflection = new Reflection(this);
    refraction = new Refraction(normalFile);

    blendState[0] = new BlendState();
    blendState[1] = new BlendState();
    blendState[1]->Alpha(true);

    mesh = new Mesh<VertexUV>();
    MakeMesh();
    mesh->CreateMesh();
}

Water::~Water()
{
    delete mesh;

    delete reflection;
    delete refraction;

    delete blendState[0];
    delete blendState[1];
}

void Water::Update()
{
    reflection->Update();
    refraction->Update();

    UpdateWorld();
}

void Water::Render()
{
    SetRender();

    reflection->SetRender();
    refraction->SetRender();

    blendState[1]->SetState();
    mesh->Draw();
    blendState[0]->SetState();
}

void Water::GUIRender()
{
    Transform::GUIRender();
    refraction->GUIRender();
}

void Water::SetReflection()
{
    reflection->SetReflection();
}

void Water::SetRefraction()
{
    refraction->SetRefraction();
}

void Water::MakeMesh()
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
