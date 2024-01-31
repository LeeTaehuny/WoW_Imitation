#pragma once

struct Vertex
{
    Float3 pos;

    Vertex()
    {
        pos = { 0.0f, 0.0f, 0.0f };
    }

    Vertex(float x, float y, float z)
    {
        pos = { x, y, z };
    }
};

struct VertexUV
{    
    Float3 pos;
    Float2 uv;

    VertexUV() : pos(0, 0, 0), uv(0, 0)
    {
    }

    VertexUV(float x, float y, float z, float u, float v)
        : pos(x, y, z), uv(u, v)
    {     
    }
};

struct VertexColor
{
    Float3 pos;
    Float4 color;

    VertexColor()
    {
        pos = { 0.0f, 0.0f, 0.0f };
        color = { 1, 1, 1, 1 };
    }

    VertexColor(float x, float y, float z, float r, float g, float b)
    {
        pos = { x, y, z };
        color = { r, g, b, 1 };
    }
};

struct VertexUVNormal
{
    Float3 pos;
    Float2 uv;
    Float3 normal;

    VertexUVNormal() : pos(0, 0, 0), uv(0, 0), normal(0, 0, 0)
    {
    }
};

struct VertexUVNormalTangent
{
    Float3 pos;
    Float2 uv;
    Float3 normal;
    Float3 tangent;

    VertexUVNormalTangent()
        : pos(0, 0, 0), uv(0, 0), normal(0, 0, 0), tangent(0, 0, 0)
    {
    }
};

struct VertexUVNormalTangentBlend
{
    Float3 pos = {};
    Float2 uv = {};
    Float3 normal = {};
    Float3 tangent = {};
    Float4 indices = {};
    Float4 weights = {};

    VertexUVNormalTangentBlend()
    {
    }
};

struct VertexUVNormalTangentAlpha
{
    Float3 pos = {};
    Float2 uv = {};
    Float3 normal = {};
    Float3 tangent = {};
    float alpha[4] = {};

    VertexUVNormalTangentAlpha()
    {
    }
};

struct InstanceData
{
    Matrix world = XMMatrixIdentity();
    int index = 0;
};