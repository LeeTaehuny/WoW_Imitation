#include "Framework.h"

Frame::Frame(wstring textureFile, Vector2 startUV, Vector2 endUV, Vector2 pos)
{
    texture = Texture::Add(textureFile);

    size = (endUV - startUV) * texture->GetSize();

    float left = pos.x - size.x * 0.5f;
    float right = pos.x + size.x * 0.5f;
    float top = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

    vertices.emplace_back(left, top, startUV.x, startUV.y);
    vertices.emplace_back(right, top, endUV.x, startUV.y);
    vertices.emplace_back(left, bottom, startUV.x, endUV.y);
    vertices.emplace_back(right, bottom, endUV.x, endUV.y);

    indices = { 0, 1, 2, 2, 1, 3 };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());
    indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

Frame::Frame(wstring textureFile, float x, float y, float width, float height)
{
    texture = Texture::Add(textureFile);

    size = { width, height };

    Vector2 halfSize = size * 0.5f;

    float left = -halfSize.x;
    float right = +halfSize.x;
    float top = +halfSize.y;
    float bottom = -halfSize.y;

    Vector2 startUV = Vector2(x, y) / texture->GetSize();
    Vector2 cutSize = size / texture->GetSize();
    Vector2 endUV = startUV + cutSize;

    vertices.emplace_back(left, top, startUV.x, startUV.y);
    vertices.emplace_back(right, top, endUV.x, startUV.y);
    vertices.emplace_back(left, bottom, startUV.x, endUV.y);
    vertices.emplace_back(right, bottom, endUV.x, endUV.y);

    indices = { 0, 1, 2, 2, 1, 3 };

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), vertices.size());
    indexBuffer = new IndexBuffer(indices.data(), indices.size());
}

Frame::~Frame()
{
    delete vertexBuffer;
    delete indexBuffer;
}

void Frame::Render()
{
    vertexBuffer->Set();
    indexBuffer->Set();

    texture->PSSet();

    DC->DrawIndexed(indices.size(), 0, 0);
}
