#pragma once

class RawBuffer
{
public:
    RawBuffer(UINT byteWidth);
    ~RawBuffer();

    void Copy(void* data, UINT size);

    ID3D11UnorderedAccessView*& GetUAV() { return uav; }

private:
    void CreateOutput();
    void CreateUAV();
    void CreateResult();

private:
    ID3D11Buffer* output;//GPU->output;
    ID3D11UnorderedAccessView* uav;

    ID3D11Buffer* result;//output->result;

    UINT byteWidth;
};
