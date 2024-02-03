#pragma once
class LastBossMap_Phase2
{
public:
    LastBossMap_Phase2();
    ~LastBossMap_Phase2();

    void Update();
    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

private:
    Model* Ground;
    
    //Collider
    Cylinder* Ground_Collider;
};

