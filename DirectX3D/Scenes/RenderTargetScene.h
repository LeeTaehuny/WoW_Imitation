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
    // �׽�Ʈ�� ��
    Model* forest;
    Human* human;

    // �׽�Ʈ�� ���� Ÿ�� �ν��Ͻ�
    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    //��¿�
    Quad* quad;                    // 2D �ؽ�ó
    FloatValueBuffer* valueBuffer; // �Ҽ� �����

};