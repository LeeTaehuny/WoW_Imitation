#pragma once
class HumanScene : public Scene
{
public:
    HumanScene();
    ~HumanScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Human* human;
    //Naruto* naruto;
};

