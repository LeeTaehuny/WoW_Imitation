#pragma once
class LastBossMap_Phase1
{
public:
    LastBossMap_Phase1();
    ~LastBossMap_Phase1();

    void Update();
    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

    void NextPhase();

private:
    Terrain* terrain;
    UINT PhaseNum = 0;

    Model* Ground;
    Model* Ground_Prop;
    Model* Obj_Prop;
    Model* Obj_Icerib[4];

    //Collider
    Cylinder* Ground_Collider;
    //Cylinder* Prop_Collider;
    Cylinder* Icerib_Collider[4];
};

