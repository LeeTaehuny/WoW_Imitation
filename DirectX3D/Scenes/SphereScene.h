#pragma once

class SphereScene : public Scene
{
public:
    SphereScene();
    ~SphereScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Sphere* sphere;
    Sphere* earth;
};