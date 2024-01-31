#include "Framework.h"

DomainShader::DomainShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(file.c_str(),
        nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "DS", "ds_5_0", flags, 0, &blob, nullptr);

    DEVICE->CreateDomainShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &shader);
}

DomainShader::~DomainShader()
{
    shader->Release();
}

void DomainShader::Set()
{
    DC->DSSetShader(shader, nullptr, 0);
}
