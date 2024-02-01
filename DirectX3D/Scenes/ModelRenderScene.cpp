#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
    model = new Model("LastBossMap1");
}

ModelRenderScene::~ModelRenderScene()
{
    delete model;
}

void ModelRenderScene::Update()
{
    model->UpdateWorld();

    if (KEY_PRESS(VK_UP))
        model->Pos().z += 100 * DELTA;

    if (KEY_PRESS(VK_DOWN))
        model->Pos().z -= 100 * DELTA;

    if (KEY_PRESS(VK_RIGHT))
        model->Pos().x += 100 * DELTA;

    if (KEY_PRESS(VK_LEFT))
        model->Pos().x -= 100 * DELTA;
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
    model->Render();
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
    model->GUIRender();
}
