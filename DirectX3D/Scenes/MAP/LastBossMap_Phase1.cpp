#include "Framework.h"

LastBossMap_Phase1::LastBossMap_Phase1()
{
    Ground = new Model("LastBossMap1");
    Ground->Scale() *= 1.0f;
    //Ground->Pos().y -= 5;
    Ground_Collider = new Cylinder();
    Ground_Collider->SetParent(Ground);
    Ground_Collider->Scale() *= 75.0f;
    Ground_Collider->Pos().y -= 33.5f;
    Ground_Collider->SetActive(false);

    Ground_Prop = new Model("LastBossMap1_B");
    Ground_Prop->Scale() *= 1.0f;
    //Ground_Prop->Pos().y -= 5;
    
    Obj_Prop = new Model("LastBossMap1_O2");
    Obj_Prop->Scale() *= 1.0f;
    Obj_Prop->Pos().y += 22.5f;
    Obj_Prop->Pos().x += 75;

    FOR(4)
    {
        Obj_Icerib[i] = new Model("LastBossMap1_O");
        Obj_Icerib[i]->Scale() *= 1.0f;
        //Obj_Icerib[i]->Pos().y -= 5;

        Icerib_Collider[i] = new Cylinder(3.5, 15, 32);
        Icerib_Collider[i]->SetParent(Obj_Icerib[i]);
        Icerib_Collider[i]->Pos().y += 10.0f;
        Icerib_Collider[i]->SetActive(false);
    }
    Obj_Icerib[0]->Pos().x += 30;
    Obj_Icerib[0]->Pos().z -= 30;
    Obj_Icerib[1]->Pos().x -= 30;
    Obj_Icerib[1]->Pos().z -= 30;
    Obj_Icerib[1]->Rot().y += 1.575f;
    Obj_Icerib[2]->Pos().x -= 30;
    Obj_Icerib[2]->Pos().z += 30;
    Obj_Icerib[2]->Rot().y += 3.15f;
    Obj_Icerib[3]->Pos().x += 30;
    Obj_Icerib[3]->Pos().z += 30;
    Obj_Icerib[3]->Rot().y -= 1.575f;

}

LastBossMap_Phase1::~LastBossMap_Phase1()
{
    delete Ground;
    delete Ground_Prop;
    delete Obj_Prop;
    FOR(4) delete Obj_Icerib[i];

    delete Ground_Collider;
    delete Icerib_Collider;
}

void LastBossMap_Phase1::Update()
{
    if (PhaseNum == 0)
    {
        Ground->UpdateWorld();
        Ground_Collider->UpdateWorld();

        FOR(4) Obj_Icerib[i]->UpdateWorld();
        FOR(4) Icerib_Collider[i]->UpdateWorld();
    }


    if (PhaseNum == 2)
    {
        Ground->UpdateWorld();
        Ground_Collider->UpdateWorld();
    }

    Ground_Prop->UpdateWorld();
    Obj_Prop->UpdateWorld();  
}

void LastBossMap_Phase1::PreRender()
{
}

void LastBossMap_Phase1::Render()
{
    if (PhaseNum == 0)
    {
        Ground->Render();
        Ground_Collider->Render();

        FOR(4) Obj_Icerib[i]->Render();
        FOR(4) Icerib_Collider[i]->Render();
    }

    if (PhaseNum == 2)
    {
        Ground->Render();
        Ground_Collider->Render();
    }
  
    Ground_Prop->Render();
    Obj_Prop->Render();
}

void LastBossMap_Phase1::PostRender()
{
}

void LastBossMap_Phase1::GUIRender()
{
}

void LastBossMap_Phase1::NextPhase()
{
    Ground->SetActive(false);
    FOR(4) Icerib_Collider[i]->SetActive(false);

    PhaseNum += 1;
}
