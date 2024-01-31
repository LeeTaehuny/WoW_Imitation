#pragma once

class IndexBuffer
{
public:
    IndexBuffer(void* data, UINT count);
    ~IndexBuffer();

    void Set();

    void Update(void* data, UINT count);

private:
    ID3D11Buffer* buffer;
};