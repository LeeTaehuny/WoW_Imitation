#include "Framework.h"

GeometryShader::GeometryShader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(file.c_str(),
        nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS", "gs_5_0", flags, 0, &blob, nullptr);

    DEVICE->CreateGeometryShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &shader);
}

GeometryShader::~GeometryShader()
{
    shader->Release();
}

void GeometryShader::Set()
{
    DC->GSSetShader(shader, nullptr, 0);
}
