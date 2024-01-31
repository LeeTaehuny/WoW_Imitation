#include "Framework.h"

PixelShader::PixelShader(wstring file)
{
    this->file = file;

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(file.c_str(),
        nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", flags, 0, &blob, nullptr);

    DEVICE->CreatePixelShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &shader);
}

PixelShader::~PixelShader()
{
    shader->Release();
}

void PixelShader::Set()
{
    DC->PSSetShader(shader, nullptr, 0);
}
