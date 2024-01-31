#pragma once

class Shader
{
protected:
    Shader() = default;
    virtual ~Shader();

public:
    static class VertexShader* AddVS(wstring file);
    static class PixelShader* AddPS(wstring file);
    static class ComputeShader* AddCS(wstring file);
    static class GeometryShader* AddGS(wstring file);
    static class HullShader* AddHS(wstring file);
    static class DomainShader* AddDS(wstring file);

    static void Delete();

    virtual void Set() = 0;

    wstring GetFile() { return file; }

protected:
    wstring file;

    ID3DBlob* blob;

    static unordered_map<wstring, Shader*> shaders;
};