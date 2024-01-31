#include "Framework.h"
#include "WaterScene.h"

WaterScene::WaterScene()
{
    skybox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
    forest = new Model("Forest");
    forest->Pos() += {0, -10, 0};
    human = new Human();

    //refraction = new Refraction(L"Textures/Landscape/Wave.dds");
    water = new Water(L"Textures/Landscape/Wave.dds", 500, 500);
}

WaterScene::~WaterScene()
{
    delete skybox;
    delete forest;
    delete human;

    //delete refraction;
    delete water;
}

void WaterScene::Update()
{
    human->Update();
    //refraction->Update();

    forest->UpdateWorld();

    water->Update();

    if (KEY_DOWN(VK_F1))
        SceneManager::Get()->Remove("Start");
}

void WaterScene::PreRender()
{
    //refraction->SetRefraction();
    water->SetRefraction();

    skybox->Render();
    forest->Render();
    human->Render();

    water->SetReflection();

    skybox->Render();
    forest->Render();
    human->Render();
}

void WaterScene::Render()
{
    skybox->Render();

    //refraction->SetRender();
    //forest->SetShader(L"Environment/Refraction.hlsl");
    forest->Render();
    water->Render();
    human->Render();
}

void WaterScene::PostRender()
{
    //refraction->PostRender();
}

void WaterScene::GUIRender()
{
    //forest->GUIRender();
    //refraction->GUIRender();
    water->GUIRender();
}
