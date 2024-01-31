#include "Framework.h"
#include "TerrainLODScene.h"

TerrainLODScene::TerrainLODScene()
{
    terrain = new TerrainLOD(L"Textures/HeightMaps/ColorMap256.png");
}

TerrainLODScene::~TerrainLODScene()
{
    delete terrain;
}

void TerrainLODScene::Update()
{
}

void TerrainLODScene::PreRender()
{
}

void TerrainLODScene::Render()
{
    terrain->Render();
}

void TerrainLODScene::PostRender()
{
}

void TerrainLODScene::GUIRender()
{
    terrain->GUIRender();
}
