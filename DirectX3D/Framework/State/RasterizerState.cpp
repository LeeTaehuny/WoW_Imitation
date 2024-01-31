#include "Framework.h"

RasterizerState::RasterizerState()
{
    desc.CullMode = D3D11_CULL_BACK;
    desc.FillMode = D3D11_FILL_SOLID;

    Changed();
}

RasterizerState::~RasterizerState()
{
    state->Release();
}

void RasterizerState::SetState()
{
    DC->RSSetState(state);
}

void RasterizerState::FillMode(D3D11_FILL_MODE value)
{
    desc.FillMode = value;

    Changed();
}

void RasterizerState::CullMode(D3D11_CULL_MODE value)
{
    desc.CullMode = value;

    Changed();
}

void RasterizerState::FrontCounterClockwise(bool value)
{
    desc.FrontCounterClockwise = value;

    Changed();
}

void RasterizerState::Changed()
{
    if (state != nullptr)
        state->Release();

    DEVICE->CreateRasterizerState(&desc, &state);
}
