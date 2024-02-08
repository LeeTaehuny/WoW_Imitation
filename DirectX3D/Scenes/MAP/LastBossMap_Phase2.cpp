#include "Framework.h"

LastBossMap_Phase2::LastBossMap_Phase2()
{
    Ground = new Model("LastBossMap2");
    Ground->Scale() *= 1.0f;
    //Ground->Pos().y -= 5;
    Ground_Collider = new Cylinder();
    Ground_Collider->SetParent(Ground);
    Ground_Collider->Scale() *= 50.0f;
    Ground_Collider->Pos().y -= 21.5f;
    Ground_Collider->SetActive(false);

    IceBreak = new IceEdges();
}

LastBossMap_Phase2::~LastBossMap_Phase2()
{
    delete Ground;
    delete Ground_Collider;
    delete IceBreak;
}

void LastBossMap_Phase2::Update()
{
    Ground->UpdateWorld();
    Ground_Collider->UpdateWorld();

    IceBreak->Update();

    if (KEY_DOWN(VK_DOWN)) IceBreak->ZeroSet();
}

void LastBossMap_Phase2::PreRender()
{
}

void LastBossMap_Phase2::Render()
{
    Ground->Render();
    Ground_Collider->Render();

    IceBreak->Render();
}

void LastBossMap_Phase2::PostRender()
{
}

void LastBossMap_Phase2::GUIRender()
{
}
