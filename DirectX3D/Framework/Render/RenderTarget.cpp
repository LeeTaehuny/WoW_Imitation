#include "Framework.h"

RenderTarget::RenderTarget(UINT width, UINT height, DXGI_FORMAT format)
    : width(width), height(height), format(format)
{
    CreateRTVTexture();
    CreateRTV();
    CreateSRV();
}

RenderTarget::~RenderTarget()
{
    rtvTexture->Release();
    rtv->Release();
    srv->Release();    
}

void RenderTarget::Set(DepthStencil* depthStencil, Float4 clearColor)
{
    DC->OMSetRenderTargets(1, &rtv, depthStencil->GetDSV());

    DC->ClearRenderTargetView(rtv, (float*)&clearColor);
    depthStencil->Clear();
        
    Environment::Get()->Set();
    Environment::Get()->SetViewport(width, height);
}

void RenderTarget::SetMulti(RenderTarget** targets, UINT count, DepthStencil* depthStencil, Float4 clearColor)
{
    vector<ID3D11RenderTargetView*> rtvs;

    FOR(count)
    {
        rtvs.push_back(targets[i]->GetRTV());
        DC->ClearRenderTargetView(rtvs.back(), (float*)&clearColor);
    }        
    depthStencil->Clear();

    DC->OMSetRenderTargets(count, rtvs.data(), depthStencil->GetDSV());

    Environment::Get()->Set();    
}

void RenderTarget::CreateRTVTexture()
{
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

    DEVICE->CreateTexture2D(&desc, nullptr, &rtvTexture);
}

void RenderTarget::CreateRTV()
{
    D3D11_RENDER_TARGET_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    DEVICE->CreateRenderTargetView(rtvTexture, &desc, &rtv);
}

void RenderTarget::CreateSRV()
{
    D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    desc.Texture2D.MipLevels = 1;

    DEVICE->CreateShaderResourceView(rtvTexture, &desc, &srv);
}