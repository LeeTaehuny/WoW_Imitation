#include "Framework.h"

Shadow::Shadow(UINT width, UINT height)
    : width(width), height(height)
{
    renderTarget = new RenderTarget(width, height);
    depthStencil = new DepthStencil(width, height);

    viewBuffer = new ViewBuffer();
    projectionBuffer = new MatrixBuffer();

    quad = new Quad(Vector2(200, 200));
    quad->Pos() = { 100, 100, 0.0f };
    quad->UpdateWorld();
    Texture* texture = Texture::Add(L"DepthMap", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);    
}

Shadow::~Shadow()
{
    delete renderTarget;
    delete depthStencil;

    delete viewBuffer;
    delete projectionBuffer;

    delete quad;
}

void Shadow::SetRenderTarget()
{
    renderTarget->Set(depthStencil);
    SetViewProjection();
}

void Shadow::SetRender()
{
    viewBuffer->SetVS(11);
    projectionBuffer->SetVS(12);

    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV());
}

void Shadow::PostRender()
{
    quad->Render();
}

void Shadow::GUIRender()
{
    ImGui::SliderFloat("Scale", &scale, 1.0f, 10.0f);
}

void Shadow::SetViewProjection()
{
    LightBuffer::Light* light = Environment::Get()->GetLight(0);

    Matrix view = XMMatrixLookAtLH(Vector3(light->pos),
        Vector3(), Vector3(0, 1, 0));
    
    Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.1f, 5000.0f);

    viewBuffer->Set(view, XMMatrixInverse(nullptr, view));
    projectionBuffer->Set(projection);

    viewBuffer->SetVS(1);
    projectionBuffer->SetVS(2);
}
