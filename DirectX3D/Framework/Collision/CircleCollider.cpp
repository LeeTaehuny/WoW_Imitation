#include "Framework.h"

CircleCollider::CircleCollider(float radius)
    : radius(radius)
{
    type = Type::CIRCLE;

    vertices.reserve(VERTEX_COUNT + 1);

    float theta = XM_2PI / VERTEX_COUNT;
    for (UINT i = 0; i <= VERTEX_COUNT; i++)
    {
        float x = cos(theta * i) * radius;
        float y = sin(theta * i) * radius;

        vertices.emplace_back(x, y);
    }

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(VertexPos), vertices.size());
}

bool CircleCollider::IsPointCollision(Vector2 point)
{
    float distance = Distance(point, GlobalPos());

    return distance < Radius();
}

bool CircleCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    return rect->IsCircleCollision(this);
}

bool CircleCollider::IsCircleCollision(CircleCollider* circle)
{
    float distance = Distance(circle->GlobalPos(), GlobalPos());

    return distance < Radius() + circle->Radius();
}

bool CircleCollider::PushCollider(Collider* collider)
{
    return false;
}
