#include "Framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring imageFile, float width, float height, UINT frameCol, UINT frameRow, bool isAdditive)
    : size(width, height)
{
    material->SetShader(L"Geometry/Sprite.hlsl");
    material->SetDiffuseMap(imageFile);

    geometryShader = Shader::AddGS(L"Geometry/Sprite.hlsl");

    buffer = new SpriteBuffer();
    buffer->Get().maxFrame = { (float)frameCol, (float)frameRow };
    maxFrameCount = frameCol * frameRow;

    if (isAdditive) blendState[1]->Additive();

    Create();
}

Sprite::~Sprite()
{
    delete buffer;
}

void Sprite::Update()
{
    if (!isActive) return;

    //2D �ִϸ��̼� ����� ���� ������� ������Ʈ

    time += speed * DELTA;

    if (time > 0.1f) //0.1f : ������ ���ؽð�. ���߿� �����ڰ� ���� ����
    {
        curFrameCount++; //������ +1
        //������ ��ġ ã��
        buffer->Get().curFrame.x = curFrameCount % (UINT)buffer->Get().maxFrame.x;
        buffer->Get().curFrame.y = curFrameCount / (UINT)buffer->Get().maxFrame.y;
        time = 0;
    }

    if (curFrameCount >= maxFrameCount) Stop();
}

void Sprite::Render()
{
    buffer->SetPS(10);
    Particle::Render();
}

void Sprite::GUIRender()
{
}

void Sprite::Play(Vector3 pos)
{
    isActive = true; //�������

    time = 0;
    curFrameCount = 0;

    vertex.pos = pos;
    vertex.uv = size;

    vertexBuffer->Update(&vertex, particleCount);
}

void Sprite::Create()
{
    particleCount = 1; //�ִϸ��̼��� ����ϴ� ���� �����̴ϱ�

    vertexBuffer = new VertexBuffer(&vertex, sizeof(VertexUV), 1); // �ؽ�ó �� �� ����� �����̴ϱ�
}
