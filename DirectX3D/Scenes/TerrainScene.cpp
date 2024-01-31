#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
    terrain = new Terrain();    

    cylinder = new Cylinder();
    cylinder->Rot().z = XM_PIDIV2;
}

TerrainScene::~TerrainScene()
{
    delete terrain;
    delete cylinder;
}

void TerrainScene::Update()
{    
    if (KEY_PRESS(VK_UP))
        cylinder->Pos().z += 100 * DELTA;

    if (KEY_PRESS(VK_DOWN))
        cylinder->Pos().z -= 100 * DELTA;

    if (KEY_PRESS(VK_RIGHT))
        cylinder->Pos().x += 100 * DELTA;

    if (KEY_PRESS(VK_LEFT))
        cylinder->Pos().x -= 100 * DELTA;

    Vector3 normal;

    cylinder->Pos().y = terrain->GetHeight(cylinder->Pos(), &normal);
    cylinder->Rot() = GetRotFromNormal(normal);

    //terrain->Rot().y += DELTA;
    terrain->UpdateWorld();
    cylinder->UpdateWorld();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
    terrain->Render();
    cylinder->Render();
}

void TerrainScene::PostRender()
{
}

void TerrainScene::GUIRender()
{
    terrain->GUIRender();
    cylinder->GUIRender();
}
