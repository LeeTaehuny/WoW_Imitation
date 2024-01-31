#pragma once

class HullShader : public Shader
{
private:
    friend class Shader;

    HullShader(wstring file);
    ~HullShader();

public:
    virtual void Set() override;

private:
    ID3D11HullShader* shader;
};