#pragma once

class Sphere : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;

public:
    Sphere(float radius = 1.0f, UINT sliceCount = 32, UINT stackCount = 16);
    ~Sphere();

    void Render() override;

private:
    void MakeMesh();
    void MakeTangent();

private:
    Mesh<VertexType>* mesh;

    float radius;
    UINT sliceCount, stackCount;
};