#include "Framework.h"

BinaryReader::BinaryReader(string filePath)
{
    file = CreateFileA(filePath.c_str(), GENERIC_READ,
        FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryReader::BinaryReader(wstring filePath)
{
    file = CreateFile(filePath.c_str(), GENERIC_READ,
        FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryReader::~BinaryReader()
{
    CloseHandle(file);
}

int BinaryReader::Int()
{
    int temp;
    ReadFile(file, &temp, sizeof(int), &size, nullptr);

    return temp;
}

UINT BinaryReader::UInt()
{
    UINT temp;
    ReadFile(file, &temp, sizeof(UINT), &size, nullptr);

    return temp;
}

float BinaryReader::Float()
{
    float temp;
    ReadFile(file, &temp, sizeof(float), &size, nullptr);

    return temp;
}

string BinaryReader::String()
{
    UINT strSize = UInt();

    char* temp = new char[strSize + 1];
    ReadFile(file, temp, sizeof(char) * strSize, &size, nullptr);
    temp[strSize] = '\0';

    return temp;
}

wstring BinaryReader::WString()
{
    UINT strSize = UInt();

    WCHAR* temp = new WCHAR[strSize + 1];
    ReadFile(file, temp, sizeof(WCHAR) * strSize, &size, nullptr);
    temp[strSize] = '\0';

    return temp;
}

Vector3 BinaryReader::Vector()
{
    Vector3 result;
    result.x = Float();
    result.y = Float();
    result.z = Float();

    return result;
}

bool BinaryReader::Bool()
{
    bool temp;
    ReadFile(file, &temp, sizeof(bool), &size, nullptr);

    return temp;
}

XMMATRIX BinaryReader::Matrix()
{
    XMMATRIX temp;
    ReadFile(file, &temp, sizeof(XMMATRIX), &size, nullptr);

    return temp;
}

void BinaryReader::Byte(void** data, UINT dataSize)
{
    ReadFile(file, *data, dataSize, &size, nullptr);
}
