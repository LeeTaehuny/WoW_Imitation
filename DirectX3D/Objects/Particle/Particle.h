#pragma once
class Particle
{
protected:
    UINT MAX_COUNT = 1000;

public:
    Particle();
    ~Particle();

    virtual void Update() {}
    virtual void Render();
    virtual void GUIRender() {}

    virtual void Play(Vector3 pos);
    void Stop();

protected:
    bool isActive = false; //활성화 여부 따로 설정 (기본값 : 처음에는 재생 안 함)
    UINT particleCount = 0; //생성시 파티클 개수 없음
    Vector3 position;

    Material* material; //시각화
    VertexBuffer* vertexBuffer; //정점(위치)

    //지오메트리 셰이더
    GeometryShader* geometryShader;

    BlendState* blendState[2];
    DepthStencilState* depthState[2];
};

