#include "Framework.h"
#include "BuffParticle.h"

BuffParticle::BuffParticle(int spawnCount) : spawnCount(spawnCount)
{
    material->SetShader(L"Geometry/Rain.hlsl");
    material->SetDiffuseMap(L"Textures/Effect/Rain.png");

    geometryShader = Shader::AddGS(L"Geometry/Rain.hlsl");

    buffer = new BuffBuffer();

    Create();
}

BuffParticle::~BuffParticle()
{
    delete buffer;
}

void BuffParticle::Update()
{
    buffer->Get().time += DELTA;
}

void BuffParticle::Render()
{
    buffer->SetVS(10);
    Particle::Render();
}

void BuffParticle::GUIRender()
{

}

void BuffParticle::Create()
{
    int count = spawnCount;
    buffer->Get().velocity = { 0, -5, 0 };

    particleCount = (count < MAX_COUNT) ? count : MAX_COUNT;

    vertices.resize(particleCount);
    FOR(particleCount)
    {
        Float2 size;
        size.x = Random(0.1f, 0.4f);
        size.y = Random(2.0f, 8.0f);

        Float3 pos;
        pos.x = Random(-buffer->Get().size.x, buffer->Get().size.x);
        pos.y = Random(-buffer->Get().size.y, buffer->Get().size.y);
        pos.z = Random(-buffer->Get().size.z, buffer->Get().size.z);

        vertices[i].pos = pos;
        vertices[i].uv = size;
    }

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), particleCount);
}
