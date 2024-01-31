#include "Framework.h"

HullShader::HullShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(file.c_str(),
        nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "HS", "hs_5_0", flags, 0, &blob, nullptr);

    DEVICE->CreateHullShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &shader);
}

HullShader::~HullShader()
{
    shader->Release();
}

void HullShader::Set()
{
    DC->HSSetShader(shader, nullptr, 0);
}
