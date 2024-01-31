#include "Framework.h"

Snow::Snow()
{
    material->SetShader(L"Geometry/Snow.hlsl");
    material->SetDiffuseMap(L"Textures/Effect/Snow.png");

    geometryShader = Shader::AddGS(L"Geometry/Snow.hlsl");

    buffer = new WeatherBuffer();

    Create();
}

Snow::~Snow()
{
    delete buffer;
}

void Snow::Update()
{
    buffer->Get().time += DELTA;
}

void Snow::Render()
{
    buffer->SetVS(10);
    Particle::Render();
}

void Snow::GUIRender()
{
    ImGui::Text("Snow Option");
    ImGui::DragFloat3("Velocity", (float*)&buffer->Get().velocity, 0.1f);
    ImGui::SliderFloat("Distance", &buffer->Get().distance, 0.0f, 500.0f);
    ImGui::DragFloat3("Origin", (float*)&buffer->Get().origin, 0.1f);
    ImGui::DragFloat3("Size", (float*)&buffer->Get().size, 0.1f);
    ImGui::SliderFloat("Turbulence", &buffer->Get().turbulence, 0.0f, 10.0f);

    ImGui::ColorEdit4("Color", (float*)&buffer->Get().color);
}

void Snow::Create()
{
    particleCount = MAX_COUNT;

    vertices.resize(particleCount);

    FOR(particleCount)
    {
        Float2 size;
        size.x = Random(0.5f, 2.0f);
        size.y = size.x;

        Float3 pos;
        pos.x = Random(-buffer->Get().size.x, buffer->Get().size.x);
        pos.y = Random(-buffer->Get().size.y, buffer->Get().size.y);
        pos.z = Random(-buffer->Get().size.z, buffer->Get().size.z);

        vertices[i].pos = pos;
        vertices[i].size = size;

        vertices[i].random.x = Random(0.0f, 1.0f);
        vertices[i].random.y = Random(0.0f, 1.0f);
    }

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexSnow), particleCount);
}
