#pragma once

class ComputeShader : public Shader
{
private:
    friend class Shader;

    ComputeShader(wstring file);
    ~ComputeShader();

public:
    virtual void Set() override;

private:
    ID3D11ComputeShader* shader;
};