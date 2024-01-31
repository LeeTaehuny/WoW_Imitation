#pragma once

class BoxCollider : public Collider
{
public:
    struct ObbDesc
    {
        Vector3 pos;
        Vector3 axis[3];
        Vector3 halfSize;
    };

public:
    BoxCollider(Vector3 size = Vector3(1, 1, 1));
    ~BoxCollider() = default;
        
    virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact) override;

    virtual bool IsBoxCollision(BoxCollider* collider) override;
    virtual bool IsSphereCollision(SphereCollider* collider) override;
    virtual bool IsCapsuleCollision(CapsuleCollider* collider) override;

    void GetObb(ObbDesc& obbDesc);    

private:
    bool IsSeperateAxis(Vector3 D, Vector3 axis, ObbDesc box1, ObbDesc box2);

private:
    virtual void MakeMesh() override;

private:
    Vector3 size;
};