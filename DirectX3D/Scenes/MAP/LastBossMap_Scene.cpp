#include "Framework.h"
#include "LastBossMap_Scene.h"

LastBossMap_Scene::LastBossMap_Scene()
{
    //terrain = new Terrain("Textures / Landscape / Tile_Ice.png");


    Phase1 = new LastBossMap_Phase1();
    Phase2 = new LastBossMap_Phase2();
}

LastBossMap_Scene::~LastBossMap_Scene()
{
    //delete terrain;

    delete Phase1;
    delete Phase2;
}

void LastBossMap_Scene::Update()
{
    //terrain->UpdateWorld();

    if (PhaseNum == 0) Phase1->Update();

    if (PhaseNum == 1)
    {
        Phase1->NextPhase();
        Phase2->Update();
    }

    if (PhaseNum == 2) 
    {
        Phase1->NextPhase();
        Phase1->Update();
    }

    if (PhaseNum >= 3)
    {
        Phase1->NextPhase();
        Phase2->Update();
    }

    if(KEY_DOWN(VK_RIGHT))
    {
        Phase1->NextPhase();    
        Phase2->Update();
    }
}

void LastBossMap_Scene::PreRender()
{

}

void LastBossMap_Scene::Render()
{
    //terrain->Render();

    Phase1->Render();
    Phase2->Render();
}

void LastBossMap_Scene::PostRender()
{
}

void LastBossMap_Scene::GUIRender()
{
    //Phase1->GUIRender();
}
