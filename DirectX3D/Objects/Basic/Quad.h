#pragma once

class Quad : public GameObject
{
private:
    typedef VertexUV VertexType;

public:
    Quad(Vector2 size);    
    Quad(wstring file);
    ~Quad();

    void Render();
    void SetRender();

private:
    void MakeMesh();

protected:
    Vector2 size;
    ColorBuffer* colorBuffer = nullptr;
    Mesh<VertexType>* mesh;    
};