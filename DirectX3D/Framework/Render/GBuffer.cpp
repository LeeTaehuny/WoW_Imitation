#include "Framework.h"

GBuffer::GBuffer()
{
    //diffuseRender = new RenderTarget(WIN_WIDTH, WIN_HEIGHT, DXGI_FORMAT_R8G8B8A8_UNORM);
    //specularRender = new RenderTarget(WIN_WIDTH, WIN_HEIGHT, DXGI_FORMAT_R8G8B8A8_UNORM);
    //normalRender = new RenderTarget(WIN_WIDTH, WIN_HEIGHT, DXGI_FORMAT_R8G8B8A8_UNORM);
    
    diffuseRender = new RenderTarget();
    specularRender = new RenderTarget();
    normalRender = new RenderTarget();

    depthStencil = new DepthStencil(WIN_WIDTH, WIN_HEIGHT, true);

    rtvs[0] = diffuseRender;
    rtvs[1] = specularRender;
    rtvs[2] = normalRender;

    srvs[0] = depthStencil->GetSRV();
    srvs[1] = diffuseRender->GetSRV();
    srvs[2] = specularRender->GetSRV();
    srvs[3] = normalRender->GetSRV();

    FOR(4)
    {
        quads[i] = new Quad(Vector2(200, 200));
        quads[i]->Pos() = { 100 + (float)i * 200, 100, 0 };
        Texture* texture = Texture::Add(L"G" + to_wstring(i), srvs[i]);
        quads[i]->GetMaterial()->SetDiffuseMap(texture);
        quads[i]->UpdateWorld();
    }
}

GBuffer::~GBuffer()
{
    delete diffuseRender;
    delete specularRender;
    delete normalRender;
    delete depthStencil;

    for (Quad* quad : quads)
        delete quad;
}

void GBuffer::PostRender()
{
    for (Quad* quad : quads)
        quad->Render();
}

void GBuffer::SetSRVs()
{
    FOR(4)
    {
        DC->PSSetShaderResources(10 + i, 1, &srvs[i]);
    }
}

void GBuffer::SetMultiRenderTarget()
{
    RenderTarget::SetMulti(rtvs, 3, depthStencil);
}
