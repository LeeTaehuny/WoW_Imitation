#include "Framework.h"
#include "ModelRenderScene.h"

ModelRenderScene::ModelRenderScene()
{
    model = new Model("LastBossMap2");
    model->Scale() *= 1.0f;
    model->Pos().y -= 5;

    model2 = new Model("LastBossMap1_B");
    model2->Scale() *= 1.0f;
    model2->Pos().y -= 5;

    model3 = new Model("LastBossMap1_O2");
    model3->Scale() *= 1.0f;
    model3->Pos().y += 22.5f;
    model3->Pos().x += 75;

    FOR(4)
    {
        model4[i] = new Model("LastBossMap1_O");
        model4[i]->Scale() *= 1.0f;
        model4[i]->Pos().y -= 5;
    }
    model4[0]->Pos().x += 30;
    model4[0]->Pos().z -= 30;
    model4[1]->Pos().x -= 30;
    model4[1]->Pos().z -= 30;
    model4[1]->Rot().y += 1.575f;
    model4[2]->Pos().x -= 30;
    model4[2]->Pos().z += 30;
    model4[2]->Rot().y += 3.15f;
    model4[3]->Pos().x += 30;
    model4[3]->Pos().z += 30;
    model4[3]->Rot().y -= 1.575f;
    
}

ModelRenderScene::~ModelRenderScene()
{
    delete model;
    delete model2;
    delete model3;
    FOR(4) delete model4[i];
}

void ModelRenderScene::Update()
{
    model->UpdateWorld();
    model2->UpdateWorld();
    model3->UpdateWorld();
    FOR(4) model4[i]->UpdateWorld();

    if (KEY_PRESS(VK_UP))
    {
        model->Pos().z += 100 * DELTA;
        model2->Pos().z += 100 * DELTA;
    }
        

    if (KEY_PRESS(VK_DOWN))
        model->Pos().z -= 100 * DELTA;

    if (KEY_PRESS(VK_RIGHT))
        model->Pos().x += 100 * DELTA;

    if (KEY_PRESS(VK_LEFT))
        model->Pos().x -= 100 * DELTA;

    if (KEY_PRESS('Z'))
        model->Pos().y -= 100 * DELTA;

    if (KEY_PRESS('C'))
        model->Pos().y += 100 * DELTA;
}

void ModelRenderScene::PreRender()
{
}

void ModelRenderScene::Render()
{
    model->Render();
    model2->Render();
    model3->Render();
    FOR(4) model4[i]->Render();
}

void ModelRenderScene::PostRender()
{
}

void ModelRenderScene::GUIRender()
{
    model->GUIRender();
}
