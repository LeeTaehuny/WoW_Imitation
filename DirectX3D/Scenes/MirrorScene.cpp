#include "Framework.h"
#include "MirrorScene.h"

MirrorScene::MirrorScene()
{
    skybox = new SkyBox(L"Textures/Landscape/BlueSky.dds");
    forest = new Model("Forest");
    forest->Pos() += {0, -10, 0};
    human = new Human();

    mirror = new Reflector(500, 500);
    mirror->GetReflection()->reflectAxis = Reflection::DIRECTION::Y;
    mirror->Pos() = { 0, 200, -200 };
    mirror->Rot() = { XM_PIDIV2, 0, 0 };
    mirror->UpdateWorld();
}

MirrorScene::~MirrorScene()
{
    delete skybox;
    delete forest;
    delete human;

    delete mirror;
}

void MirrorScene::Update()
{
    human->Update();

    forest->UpdateWorld();

    mirror->Update();
}

void MirrorScene::PreRender()
{
    skybox->Render();
    forest->Render();
    human->Render();

    mirror->SetReflection();

    skybox->Render();
    forest->Render();
    human->Render();
}

void MirrorScene::Render()
{
    skybox->Render();
    forest->Render();

    mirror->Render();

    human->Render();
}

void MirrorScene::PostRender()
{
}

void MirrorScene::GUIRender()
{
    mirror->GUIRender();
}
