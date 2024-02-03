#pragma once

class LastBossMap_Scene : public Scene
{
public:
    LastBossMap_Scene();
    ~LastBossMap_Scene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Terrain* terrain;

    UINT PhaseNum = 0;

    // Phase Ground
    LastBossMap_Phase1* Phase1;
    LastBossMap_Phase2* Phase2;
};

