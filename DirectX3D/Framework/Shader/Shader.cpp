#include "Framework.h"

unordered_map<wstring, Shader*> Shader::shaders;

Shader::~Shader()
{
    blob->Release();
}

VertexShader* Shader::AddVS(wstring file)
{   
    if (file.size() == 0)
        file = L"Light/Light.hlsl";

    wstring key = file + L"VS";    

    if (shaders.count(key) > 0)
        return (VertexShader*)shaders[key];

    wstring path = L"Shaders/" + file;    

    shaders[key] = new VertexShader(path);

    return (VertexShader*)shaders[key];
}

PixelShader* Shader::AddPS(wstring file)
{
    if (file.size() == 0)
        file = L"Light/Light.hlsl";

    wstring key = file + L"PS";

    if (shaders.count(key) > 0)
        return (PixelShader*)shaders[key];

    wstring path = L"Shaders/" + file;

    shaders[key] = new PixelShader(path);

    return (PixelShader*)shaders[key];
}

ComputeShader* Shader::AddCS(wstring file)
{
    wstring key = file;

    if (shaders.count(key) > 0)
        return (ComputeShader*)shaders[key];

    wstring path = L"Shaders/" + file;

    shaders[key] = new ComputeShader(path);

    return (ComputeShader*)shaders[key];
}

GeometryShader* Shader::AddGS(wstring file)
{
    wstring key = file;

    if (shaders.count(key) > 0)
        return (GeometryShader*)shaders[key];

    wstring path = L"Shaders/" + file;

    shaders[key] = new GeometryShader(path);

    return (GeometryShader*)shaders[key];
}

HullShader* Shader::AddHS(wstring file)
{
    wstring key = file + L"HS";

    if (shaders.count(key) > 0)
        return (HullShader*)shaders[key];

    wstring path = L"Shaders/" + file;

    shaders[key] = new HullShader(path);

    return (HullShader*)shaders[key];
}

DomainShader* Shader::AddDS(wstring file)
{
    wstring key = file + L"DS";

    if (shaders.count(key) > 0)
        return (DomainShader*)shaders[key];

    wstring path = L"Shaders/" + file;

    shaders[key] = new DomainShader(path);

    return (DomainShader*)shaders[key];
}

void Shader::Delete()
{
    for (pair<wstring, Shader*> shader : shaders)
        delete shader.second;
}
