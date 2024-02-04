#include "Framework.h"
#include "LastBossMap_Scene.h"
#include "Objects/MAP/BossMap.h"

LastBossMap_Scene::LastBossMap_Scene()
{
    //terrain = new Terrain("Textures / Landscape / Tile_Ice.png");
    //bossmap = new BossMap();

    Phase1 = new LastBossMap_Phase1();
    Phase2 = new LastBossMap_Phase2();

    //Test = new SphereCollider(2);
    //Test->Pos().x -= 100;
}

LastBossMap_Scene::~LastBossMap_Scene()
{
    //delete terrain;

    delete Phase1;
    delete Phase2;
    //delete Test;

    //delete bossmap;
}

void LastBossMap_Scene::Update()
{
    //terrain->UpdateWorld();

    Phase1->Update();

    if(Phase1->GetPhaseNum() == 1 || Phase1->GetPhaseNum() == 3)
    {
        Phase2->Update();
    }
    if(KEY_DOWN(VK_RIGHT))
    {
        Phase1->NextPhase();
    }

    //bossmap->Update();

    //if (KEY_DOWN('W')) Test->Pos().y += 150;
    //if (KEY_DOWN('S')) Test->Pos().y -= 150;
    //Test->UpdateWorld();
}

void LastBossMap_Scene::PreRender()
{

}

void LastBossMap_Scene::Render()
{
    //terrain->Render();

    Phase1->Render();
    Phase2->Render();

    //Test->Render();
}

void LastBossMap_Scene::PostRender()
{
}

void LastBossMap_Scene::GUIRender()
{
    //Phase1->GUIRender();
}
