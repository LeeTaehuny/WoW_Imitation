#pragma once

class PixelShader : public Shader
{
private:
    friend class Shader;

    PixelShader(wstring file);
    ~PixelShader();

public:
    virtual void Set() override;

private:
    ID3D11PixelShader* shader;    
};