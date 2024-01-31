#include "Framework.h"

BinaryWriter::BinaryWriter(string filePath)
{
    file = CreateFileA(filePath.c_str(), GENERIC_WRITE,
        0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryWriter::BinaryWriter(wstring filePath)
{
    file = CreateFile(filePath.c_str(), GENERIC_WRITE,
        0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryWriter::~BinaryWriter()
{
    CloseHandle(file);
}

void BinaryWriter::Int(int data)
{
    WriteFile(file, &data, sizeof(int), &size, nullptr);
}

void BinaryWriter::UInt(UINT data)
{
    WriteFile(file, &data, sizeof(UINT), &size, nullptr);
}

void BinaryWriter::Float(float data)
{
    WriteFile(file, &data, sizeof(float), &size, nullptr);
}

void BinaryWriter::String(string data)
{
    UInt(data.size());

    const char* str = data.c_str();
    WriteFile(file, str, sizeof(char) * data.size(), &size, nullptr);
}

void BinaryWriter::WString(wstring data)
{
    UInt(data.size());

    const WCHAR* str = data.c_str();
    WriteFile(file, str, sizeof(WCHAR) * data.size(), &size, nullptr);
}

void BinaryWriter::Vector(Vector3 data)
{
    Float(data.x);
    Float(data.y);
    Float(data.z);
}

void BinaryWriter::Bool(bool data)
{
    WriteFile(file, &data, sizeof(bool), &size, nullptr);
}

void BinaryWriter::Matrix(XMMATRIX data)
{
    WriteFile(file, &data, sizeof(XMMATRIX), &size, nullptr);
}

void BinaryWriter::Byte(void* data, UINT dataSize)
{
    WriteFile(file, data, dataSize, &size, nullptr);
}
