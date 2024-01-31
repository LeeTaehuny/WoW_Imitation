#include "Framework.h"

Spark::Spark(wstring imageFile, bool isAdditive)
{
    material->SetShader(L"Geometry/Spark.hlsl");
    material->SetDiffuseMap(imageFile);

    geometryShader = Shader::AddGS(L"Geometry/Spark.hlsl");

    buffer = new FloatValueBuffer();
    startColorBuffer = new ColorBuffer();
    endColorBuffer = new ColorBuffer();

    if (isAdditive)
        blendState[1]->Additive();

    Create();
}

Spark::~Spark()
{
    delete buffer;

    delete startColorBuffer;
    delete endColorBuffer;
}

void Spark::Update()
{
    if (!isActive) return;

    buffer->Get()[0] += DELTA;

    if (buffer->Get()[0] > buffer->Get()[1])
        Stop();
}

void Spark::Render()
{
    buffer->SetVS(10);
    buffer->SetPS(10);

    startColorBuffer->SetPS(11);
    endColorBuffer->SetPS(12);

    Particle::Render();
}

void Spark::GUIRender()
{
    ImGui::Text("Spark Option");
    ImGui::SliderInt("ParticleCount", (int*)&particleCount, 1, MAX_COUNT);
    ImGui::SliderFloat("Duration", &buffer->Get()[1], 0.0f, 10.0f);
    ImGui::SliderFloat("MinRadius", &minRadius, 1.0f, maxRadius);
    ImGui::SliderFloat("MaxRadius", &maxRadius, minRadius, 50.0f);
    ImGui::SliderFloat("MinSize", &minSize, 0.1f, maxSize);
    ImGui::SliderFloat("MaxSize", &maxSize, minSize, 10.0f);

    ImGui::ColorEdit4("StartColor", (float*)&startColorBuffer->Get());
    ImGui::ColorEdit4("EndColor", (float*)&endColorBuffer->Get());
}

void Spark::Play(Vector3 position)
{
    buffer->Get()[0] = 0.0f;

    Particle::Play(position);

    UpdateParticle();
    vertexBuffer->Update(vertices.data(), particleCount);
}

void Spark::Create()
{
    vertices.resize(MAX_COUNT);
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexParticle), MAX_COUNT);

    particleCount = 500;
    buffer->Get()[1] = 1.0f;
}

void Spark::UpdateParticle()
{
    FOR(particleCount)
    {
        vertices[i].position = position;

        float size = Random(minSize, maxSize);
        vertices[i].size = { size, size };

        float radius = Random(minRadius, maxRadius);

        Float3 rot;
        rot.x = Random(0.0f, XM_2PI);
        rot.y = Random(0.0f, XM_2PI);
        rot.z = Random(0.0f, XM_2PI);

        Vector3 velocity = Vector3(0, 0, radius);

        Matrix matRot = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
        XMStoreFloat3(&vertices[i].velocity, XMVector3TransformCoord(velocity, matRot));
    }
}
