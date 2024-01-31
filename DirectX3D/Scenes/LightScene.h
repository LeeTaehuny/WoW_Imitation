#pragma once

class LightScene : public Scene
{
public:
    LightScene();
    ~LightScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Sphere* sphere;

    LightBuffer::Light* light; //광원 포인터
    TestLight* tl;
};