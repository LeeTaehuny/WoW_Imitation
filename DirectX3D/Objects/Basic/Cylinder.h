#pragma once

class Cylinder : public GameObject
{
private:
    typedef VertexUVNormalTangent VertexType;

public:
    Cylinder(float radius = 1.0f, float height = 1.0f, UINT sliceCount = 32);
    ~Cylinder();

    void Render() override;

    void SetHeight(float newHeight);

    float Radius()
    {
        float maxScale = max(GlobalScale().x, max(GlobalScale().y, GlobalScale().z));
        return radius * maxScale;
    }

    float Height()
    {
        return (height - 2 * Radius()) * GlobalScale().y;
    }

    bool IsCapsuleCollision(CapsuleCollider* collider);
    bool PushCollision(CapsuleCollider* collider);
   
private:
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();

private:
    Mesh<VertexType>* mesh;

    float radius, height;
    UINT sliceCount;
};