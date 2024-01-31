#pragma once

class DomainShader : public Shader
{
private:
    friend class Shader;

    DomainShader(wstring file);
    ~DomainShader();

public:
    virtual void Set() override;

private:
    ID3D11DomainShader* shader;
};