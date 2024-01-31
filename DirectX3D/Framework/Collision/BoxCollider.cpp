#include "Framework.h"

BoxCollider::BoxCollider(Vector3 size) : size(size)
{
    type = BOX;

    MakeMesh();
    mesh->CreateMesh();
}

bool BoxCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{
    UpdateWorld();

    ObbDesc box;
    GetObb(box);

    Vector3 min = box.halfSize * -1.0f;
    Vector3 max = box.halfSize;

    Vector3 delta = box.pos - ray.pos;

    Vector3 D = ray.dir.GetNormalized();

    float tMin = 0.0f;
    float tMax = FLT_MAX;

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 axis = box.axis[i];
        float e = Dot(axis, delta);
        float f = Dot(D, axis);

        if (NearlyEqual(f, 0.0f))//레이와 축이 수직인 상황
        {
            if (min[i] > e || max[i] < e) return false;
        }
        else
        {
            float t1 = (e + min[i]) / f;
            float t2 = (e + max[i]) / f;

            if (t1 > t2) swap(t1, t2);

            if (t2 < tMax) tMax = t2;
            if (t1 > tMin) tMin = t1;
            if (tMin > tMax) return false;
        }
    }

    if (contact != nullptr)
    {
        contact->tag = tag;
        contact->distance = tMin;
        contact->hitPoint = ray.pos + ray.dir * tMin;
    }

    return true;
}

bool BoxCollider::IsBoxCollision(BoxCollider* collider)
{
    ObbDesc box1, box2;
    GetObb(box1);
    collider->GetObb(box2);

    Vector3 D = box2.pos - box1.pos;

    for (UINT i = 0; i < 3; i++)
    {
        if (IsSeperateAxis(D, box1.axis[i], box1, box2)) return false;
        if (IsSeperateAxis(D, box2.axis[i], box1, box2)) return false;
    }

    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            if (box1.axis[i] == box2.axis[j]) return true;
        }
    }

    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            Vector3 cross = Cross(box1.axis[i], box2.axis[j]);
            if (IsSeperateAxis(D, cross, box1, box2)) return false;
        }
    }

    return true;
}

bool BoxCollider::IsSphereCollision(SphereCollider* collider)
{
    ObbDesc box;
    GetObb(box);

    Vector3 closestPointToSphere = box.pos;

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 direction = collider->GlobalPos() - box.pos;

        float length = Dot(box.axis[i], direction);

        float mult = (length < 0.0f) ? -1.0f : 1.0f;

        length = min(abs(length), box.halfSize[i]);

        closestPointToSphere += box.axis[i] * length * mult;
    }

    float distance = Distance(collider->GlobalPos(), closestPointToSphere);

    return distance <= collider->Radius();
}

bool BoxCollider::IsCapsuleCollision(CapsuleCollider* collider)
{
    return collider->IsBoxCollision(this);
}

void BoxCollider::GetObb(ObbDesc& obbDesc)
{
    obbDesc.pos = GlobalPos();

    obbDesc.axis[0] = Right();
    obbDesc.axis[1] = Up();
    obbDesc.axis[2] = Forward();

    obbDesc.halfSize = size * 0.5f * GlobalScale();
}

bool BoxCollider::IsSeperateAxis(Vector3 D, Vector3 axis, ObbDesc box1, ObbDesc box2)
{
    float distance = abs(Dot(D, axis));

    float a = 0.0f;
    float b = 0.0f;

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 temp = box1.axis[i] * box1.halfSize[i];
        a += abs(Dot(temp, axis));
        temp = box2.axis[i] * box2.halfSize[i];
        b += abs(Dot(temp, axis));
    }

    return distance > a + b;
}

void BoxCollider::MakeMesh()
{
    Vector3 halfSize = size * 0.5f;

    vector<Vertex>& vertices = mesh->GetVertices();

    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z);
    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z);
    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z);

    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z);
    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z);
    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z);

    vector<UINT>& indices = mesh->GetIndices();

    indices = {
        0, 1, 1, 3, 3, 2, 2, 0,
        4, 5, 5, 7, 7, 6, 6, 4,
        0, 4, 1, 5, 2, 6, 3, 7
    };
}
