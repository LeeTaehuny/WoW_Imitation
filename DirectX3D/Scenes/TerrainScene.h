#pragma once

class TerrainScene : public Scene
{
public:
    TerrainScene();
    ~TerrainScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Terrain* terrain;    
    Cylinder* cylinder;
};