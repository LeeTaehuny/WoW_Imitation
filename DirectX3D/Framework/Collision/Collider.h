#pragma once
#include "Objects/Basic/GameObject.h"

struct Ray
{
    Vector3 pos;
    Vector3 dir;

    Ray()
    {
    }

    Ray(Vector3 pos, Vector3 dir) : pos(pos), dir(dir)
    {
    }
};

struct Contact
{
    string tag;

    Vector3 hitPoint;
    float distance;
};

class Collider : public GameObject
{
protected:
    enum Type
    {
        BOX, SPHERE, CAPSULE
    };

    const float PUSH_SPEED = 100.0f;

public:
    Collider();
    ~Collider();

    void Render();

    bool IsCollision(Collider* collider);

    virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact = nullptr) = 0;
    virtual bool IsBoxCollision(class BoxCollider* collider) = 0;
    virtual bool IsSphereCollision(class SphereCollider* collider) = 0;
    virtual bool IsCapsuleCollision(class CapsuleCollider* collider) = 0;

    bool PushCollision(Collider* collider);
    
    void SetColor(Float4 color) { material->GetData().diffuse = color; }
    void SetColor(float r, float g, float b)
    {
        material->GetData().diffuse = { r, g, b, 1 };
    }

    static void RenderOnOff() { isRender = !isRender; }

private:
    virtual void MakeMesh() = 0;

protected:
    Type type;    

    Mesh<Vertex>* mesh;

private:
    static bool isRender;
};