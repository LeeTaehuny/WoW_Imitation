#include "Framework.h"
#include "CubeScene.h"

CubeScene::CubeScene()
{    
    cube = new Cube();
    cube->GetMaterial()->SetDiffuseMap(L"Textures/Etc/sun.jpg");
}

CubeScene::~CubeScene()
{
    delete cube;
}

void CubeScene::Update()
{
    //cube->Rot().y += DELTA;
    cube->Rot().x += DELTA;

    cube->UpdateWorld();
}

void CubeScene::PreRender()
{
}

void CubeScene::Render()
{
    cube->Render();
}

void CubeScene::PostRender()
{
}

void CubeScene::GUIRender()
{
    cube->GUIRender();
    cube->GetMaterial()->GUIRender();
}
