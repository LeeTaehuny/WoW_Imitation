#pragma once

class RasterizerState
{
public:
    RasterizerState();
    ~RasterizerState();

    void SetState();

    void FillMode(D3D11_FILL_MODE value);
    void CullMode(D3D11_CULL_MODE value);
    void FrontCounterClockwise(bool value);

    void Changed();

private:
    D3D11_RASTERIZER_DESC desc = {};
    ID3D11RasterizerState* state = nullptr;
};