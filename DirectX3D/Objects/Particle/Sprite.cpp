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

    //2D 애니메이션 재생과 같은 방식으로 업데이트

    time += speed * DELTA;

    if (time > 0.1f) //0.1f : 임의의 기준시간. 나중에 개발자가 수정 가능
    {
        curFrameCount++; //프레임 +1
        //프레임 위치 찾기
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
    isActive = true; //재생시작

    time = 0;
    curFrameCount = 0;

    vertex.pos = pos;
    vertex.uv = size;

    vertexBuffer->Update(&vertex, particleCount);
}

void Sprite::Create()
{
    particleCount = 1; //애니메이션을 재생하는 것이 목적이니까

    vertexBuffer = new VertexBuffer(&vertex, sizeof(VertexUV), 1); // 텍스처 한 개 출력이 목적이니까
}
