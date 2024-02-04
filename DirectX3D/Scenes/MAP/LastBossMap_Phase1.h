#pragma once
class LastBossMap_Phase1
{
public:
    LastBossMap_Phase1();
    ~LastBossMap_Phase1();

    void Update();
    void Render();

    void NextPhase();

    UINT GetPhaseNum() { return PhaseNum; }

private:
    UINT PhaseNum = 0;

    // Model
    Model* Ground;
    Model* Ground_Prop;
    Model* Obj_Prop;
    Model* Obj_Icerib[4];

    Model* Sky;

    // Collider
    Cylinder* Ground_Collider;
    Cylinder* Icerib_Collider[4];
};

