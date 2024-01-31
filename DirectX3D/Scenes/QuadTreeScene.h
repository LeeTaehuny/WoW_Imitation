#pragma once

class QuadTreeScene : public Scene
{
public:
    QuadTreeScene();
    ~QuadTreeScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    QuadTreeTerrain* terrain;
};