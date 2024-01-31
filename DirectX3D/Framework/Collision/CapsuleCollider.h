#pragma once

class CapsuleCollider : public Collider
{
public:
    CapsuleCollider(float radius = 1.0f, float height = 2.0f,
        UINT stackCount = 8, UINT sliceCount = 16);
    ~CapsuleCollider() = default;

    virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact) override;
    virtual bool IsBoxCollision(BoxCollider* collider) override;
    virtual bool IsSphereCollision(SphereCollider* collider) override;
    virtual bool IsCapsuleCollision(CapsuleCollider* collider) override;

    float Radius() { return radius * max(GlobalScale().x, max(GlobalScale().y, GlobalScale().z)); }
    float Height() { return height * GlobalScale().y; }

private:
    virtual void MakeMesh() override;

private:
    float radius, height;
    UINT stackCount, sliceCount;
};