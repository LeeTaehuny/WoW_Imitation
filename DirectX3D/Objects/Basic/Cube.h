#pragma once

class Cube : public GameObject
{
private:
    typedef VertexUV VertexType;

public:
    Cube(Vector3 size = Vector3(1, 1, 1));
    ~Cube();

    void Update();
    void Render();

    BoxCollider* GetCollider() { return collider; }

private:
    void MakeMesh();

private:
    Vector3 size;

    Mesh<VertexType>* mesh;
    BoxCollider* collider;
};