#pragma once

class DepthStencil
{
public:
    DepthStencil(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT, bool isStencil = false);
    ~DepthStencil();

    void Clear();

    ID3D11DepthStencilView*& GetDSV() { return dsv; }
    ID3D11ShaderResourceView*& GetSRV() { return srv; }

private:
    void CreateDSVTexture();
    void CreateDSV();
    void CreateSRV();

private:
    UINT width, height;
    bool isStencil;

    ID3D11Texture2D* dsvTexture;
    ID3D11DepthStencilView* dsv;
    ID3D11ShaderResourceView* srv;
};