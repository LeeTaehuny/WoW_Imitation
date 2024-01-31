#pragma once

class CubeScene : public Scene
{
public:
    CubeScene();
    ~CubeScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Cube* cube;
};