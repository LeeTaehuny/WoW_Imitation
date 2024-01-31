#include "Framework.h"
#include "SphereScene.h"

SphereScene::SphereScene()
{
    sphere = new Sphere();    
    //sphere->GetMaterial()->SetShader(L"Basic/Texture.hlsl");
    sphere->GetMaterial()->SetDiffuseMap(L"Textures/Etc/Sun.jpg");

    earth = new Sphere();
    earth->GetMaterial()->SetDiffuseMap(L"Textures/Etc/Earth_DM.jpg");

    earth->SetParent(sphere);
    earth->Pos().x = 10.0f;
}

SphereScene::~SphereScene()
{
    delete sphere;
    delete earth;
}

void SphereScene::Update()
{
    sphere->Rot().y += DELTA;
    sphere->UpdateWorld();

    earth->UpdateWorld();
}

void SphereScene::PreRender()
{
}

void SphereScene::Render()
{
    sphere->Render();
    earth->Render();
}

void SphereScene::PostRender()
{
}

void SphereScene::GUIRender()
{
    sphere->GUIRender();
}
