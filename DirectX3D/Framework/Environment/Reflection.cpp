#include "Framework.h"

Reflection::Reflection(Transform* target)
    : target(target)
{
    renderTarget = new RenderTarget(2048, 2048);
    depthStencil = new DepthStencil(2048, 2048);

    camera = new Camera();

    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0 };
    Texture* texture = Texture::Add(L"Reflection", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);
    quad->UpdateWorld();
}

Reflection::~Reflection()
{
    delete renderTarget;
    delete depthStencil;
    delete camera;
    delete quad;
}

void Reflection::Update()
{
    camera->Pos() = CAM->Pos();
    camera->Rot() = CAM->Rot();

    switch (reflectAxis)
    {
    case Reflection::DIRECTION::X:
        camera->Rot().x *= -1.0f;
        camera->Pos().y = target->Pos().y * 2.0f - camera->Pos().y;
        break;
    case Reflection::DIRECTION::Y: //WIP!!!
        camera->Rot().y *= -1.0f;
        {
            Vector3 dir = target->Pos() - camera->Pos();
            camera->Pos() = target->Pos() + dir;
        }
        break;
    case Reflection::DIRECTION::Z:
        //......Z축 반사라는 건 뭘까요.......
        break;
    }

    camera->UpdateWorld();
}

void Reflection::SetReflection()
{
    renderTarget->Set(depthStencil);
    camera->SetView();
}

void Reflection::SetRender()
{
    camera->GetViewBuffer()->SetVS(10);
    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV());    
}

void Reflection::PostRender()
{
    quad->Render();
}
