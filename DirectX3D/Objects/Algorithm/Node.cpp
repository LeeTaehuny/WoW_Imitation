#include "Framework.h"

Node::Node(Vector3 pos, int index)
    : index(index)
{
    // 콜라이더 정보 설정
    Pos() = pos;
    UpdateWorld();
}

Node::~Node()
{
    for (Edge* edge : edges)
        delete edge;
}

void Node::Render()
{
    switch (state)
    {
    case Node::NONE:
        SetColor({ 0, 1, 1, 1 }); // 청록색
        break;

    case Node::OPEN:
        SetColor({ 0, 0, 1, 1 }); // 파란색
        break;

    case Node::CLOSED:
        SetColor({ 0, 0, 0, 1 }); // 까만색
        break;

    case Node::USING:
        SetColor({ 0, 1, 0, 1 }); // 초록색
        break;

    case Node::OBSTACLE:
        SetColor({ 1, 0, 0, 1 }); // 빨간색
        break;
    }

    BoxCollider::Render();
}

void Node::AddEdge(Node* node)
{
    Edge* edge = new Edge();
    edge->index = node->index;
    edge->cost = Distance(node->GlobalPos(), GlobalPos()); // 콜라이더로서의 두 노드 거리

    edges.push_back(edge);
}