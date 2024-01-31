#pragma once

class MirrorScene : public Scene
{
public:
    MirrorScene();
    ~MirrorScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    SkyBox* skybox;
    Model* forest;
    Human* human;
    Reflector* mirror;
};

