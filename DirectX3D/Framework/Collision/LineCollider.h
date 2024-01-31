#pragma once

class LineCollider : public Collider
{
public:
    LineCollider(Vector2 startPos, Vector2 endPos);
    ~LineCollider() = default;

    virtual bool IsPointCollision(Vector2 point) override;
    virtual bool IsRectCollision(RectCollider* rect, Vector2* overlap) override;
    virtual bool IsCircleCollision(CircleCollider* circle) override;
    virtual bool PushCollider(Collider* collider) override;

private:
    Vector2 startPos;
    Vector2 endPos;
};