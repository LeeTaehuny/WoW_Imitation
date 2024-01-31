#pragma once
class ShadowScene : public Scene
{
public:

    ShadowScene();
    ~ShadowScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

    Model* forest;
    Human* human;

    Shadow* shadow;

};

