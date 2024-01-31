#pragma once
class GBufferScene : public Scene
{
public:
    GBufferScene();
    ~GBufferScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

    GBuffer* gBuffer;

    Model* forest;
    Human* human;

    Material* material;
    VertexBuffer* vertexBuffer;
};

