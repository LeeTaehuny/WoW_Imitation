#pragma once

class RenderTargetScene : public Scene
{
public:
    RenderTargetScene();
    ~RenderTargetScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    // 테스트용 모델
    Model* forest;
    Human* human;

    // 테스트용 렌더 타겟 인스턴스
    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    //출력용
    Quad* quad;                    // 2D 텍스처
    FloatValueBuffer* valueBuffer; // 소수 연산용

};