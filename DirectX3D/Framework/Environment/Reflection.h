#pragma once

class Reflection
{
public:
    enum class DIRECTION
    {
        X, Y, Z
    };
    DIRECTION reflectAxis = DIRECTION::X;

public:
    Reflection(Transform* target);
    ~Reflection();

    void Update();

    void SetReflection();
    void SetRender();
    void PostRender();

private:
    Transform* target;

    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    Camera* camera;

    class Quad* quad;
};