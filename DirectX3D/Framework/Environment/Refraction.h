#pragma once

class Refraction
{
public:
    Refraction(wstring normalFile);
    ~Refraction();

    void Update();

    void SetRefraction();
    void SetRender();
    void PostRender();
    void GUIRender();

private:
    WaterBuffer* waterBuffer;

    Texture* normalMap;

    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    class Quad* quad;
};