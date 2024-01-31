#pragma once

class RenderTarget
{
public:
    RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT,
        DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT);
    ~RenderTarget();

    void Set(DepthStencil* depthStencil, Float4 clearColor = Float4(1, 1, 1, 1));


    ID3D11ShaderResourceView*& GetSRV() { return srv; }
    ID3D11RenderTargetView*& GetRTV() { return rtv; }

    static void SetMulti(RenderTarget** targets, UINT count, DepthStencil* depthStencil, Float4 clearColor = Float4(1, 1, 1, 1));

private:
    void CreateRTVTexture();
    void CreateRTV();
    void CreateSRV();

private:
    UINT width, height;
    DXGI_FORMAT format;

    ID3D11Texture2D* rtvTexture;
    ID3D11RenderTargetView* rtv;
    ID3D11ShaderResourceView* srv;
};