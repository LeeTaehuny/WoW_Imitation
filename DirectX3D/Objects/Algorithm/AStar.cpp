#include "Framework.h"

AStar::AStar(UINT width, UINT height)
    : width(width), height(height)
{
    heap = new Heap();
}

AStar::~AStar()
{
    for (Node* node : nodes)
        delete node;
    delete heap;
}

void AStar::Update()
{
    // ����Ʈ+��Ŭ���ϸ� �������� ��ֹ� ���� (Ÿ�ϸ� ���� ��ü)
    if (KEY_PRESS(VK_LSHIFT))
    {
        if (KEY_DOWN(VK_RBUTTON))
        {
            Ray ray = CAM->ScreenPointToRay(mousePos);

            for (Node* node : nodes)
            {
                if (node->IsRayCollision(ray, nullptr))
                {
                    node->SetState(Node::OBSTACLE);
                    AddObstacle(node);
                    break;
                }
            }
        }
    }
}

void AStar::Render()
{
    for (Node* node : nodes)
        node->Render();
}

void AStar::GetPath(IN int start, IN int end, OUT vector<Vector3>& path)
{
    if (start == -1 || end == -1) return;

    Reset();
    path.clear();

    float _g = 0;
    float _h = GetDiagonalManhattanDistance(start, end);

    nodes[start]->f = _g + _h;
    nodes[start]->g = _g;
    nodes[start]->h = _h;
    nodes[start]->via = start;
    nodes[start]->state = Node::OPEN;

    heap->Insert(nodes[start]);

    while (nodes[end]->state != Node::CLOSED)
    {
        if (heap->Empty())
            return;
        
        int curIndex = GetMinNode();

        Extend(curIndex, end);
        nodes[curIndex]->state = Node::CLOSED;
    }

    int curIndex = end;

    while (curIndex != start)
    {
        nodes[curIndex]->state = Node::USING;
        path.push_back(nodes[curIndex]->GlobalPos()); // ����� ������� ��� �ݶ��̴��μ��� ��ġ�� ���
        curIndex = nodes[curIndex]->via;
    }

    //�� �� �����Ͱ� �ƴ϶� �ƿ� ������ ����̶�,
    //���� ��ġ = ĳ���ͳ� �־��� ��ġ�� �״�� �����ص� ����x
    //path.push_back(nodes[start]->GlobalPos());
}

void AStar::MakeDirectionPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path)
{
    //�� �Լ��� ���� : 1. ���������� �������� ���� ���� �Ÿ� ��, ���� �������� ���� ��ֹ��� �Ÿ� ����
    //                2. (1.���� ���� ����) ����������, ������ ���� ���� ��ֹ��� �� ������ �� �� �ִ� ���� �� �Ÿ�
    //                ...�� �ϳ��� ��� ����
    
    int cutNodeNum = 0;
    Ray ray;
    ray.pos = start;

    FOR(path.size())
    {
        if (!IsCollisionObstacle(start, path[i]))
        {
            cutNodeNum = path.size() - i - 1;
            break;
        }
    }

    FOR(cutNodeNum)
    {
        path.pop_back();
    }

    cutNodeNum = 0;
    ray.pos = end;

    FOR(path.size())
    {
        if (!IsCollisionObstacle(end, path[path.size() - i - 1]))
        {
            cutNodeNum = path.size() - i - 1;
            break;
        }
    }

    FOR(cutNodeNum)
    {
        path.erase(path.begin());
    }
}

bool AStar::IsCollisionObstacle(Vector3 start, Vector3 end)
{
    Ray ray(start, (end - start).GetNormalized()); //����������, ���� ���ϴ� ���� �غ�

    float distance = Distance(start, end); //�Ÿ� ����

    Contact contact; // �������� �غ�

    for (Collider* obstacle : obstacles)
    {
        if (obstacle->IsRayCollision(ray, &contact))
        {
            if (contact.distance < distance) //���������� �Ÿ��� ���������� �Ÿ����� ª����
            {
                return true; //�������� ���� �߿� ��ֹ��� �־���
            }
        }
    }

    return false;
}

void AStar::AddObstacle(Collider* collider)
{
    obstacles.push_back(collider);
}

void AStar::SetNode(Terrain* terrain)
{
    //�ͷ��� (Ȥ�� �ٸ� Ŭ������ ����) �޾ƿͼ� �ش� ��ġ�� ��� ��ġ�ϱ�

    //������ �����̹Ƿ� ���⼭�� 2������ ��ó�� ���ظ� �ص� �� ��
    //Vector2 mapSize = terrain->GetMaterial()->GetDiffuseMap()->GetSize();
    //TODO : ������ ���� ũ�Ⱑ ���� ������ �����ϴٸ� ���⼭�� ũ�⸦ �ҷ��;� �Ѵ�
    //       �� : �ͷ��� ������... (�ͷ��� Ŭ������ ���� ũ�Ⱑ �ٲ�ٸ� GetSize �ʿ�)
    //       * ������ �Ű������� ���� ���� ��� Ŭ������ GetSize�� �� �� �� �־�� �Ѵ�

    Vector2 mapSize = terrain->GetSize(); // ���� ũ�� �ݿ���

    //��ġ���� ���ϱ�
    interval.x = mapSize.x / width; //�� ũ�⸦ ��ã���� ���η� ������
    interval.y = mapSize.y / height;

    nodes.reserve((width + 1) * (height + 1)); // +1 : ũ�� ����� ���� ���� ���� ����

    for (UINT z = 0; z <= height; ++z)
    {
        for (UINT x = 0; x <= width; ++x)
        {
            //��ġ���ݰ� ���μ��� ��ǥ�� �ݿ��ؼ� ��ġ ����
            Vector3 pos = Vector3(x * interval.x, 0, z * interval.y);
            //pos.y = 0; // ���ذ� 0 : �⺻��
            //TODO : ���ذ��� �ٲ�� �� �ڵ� ������ ��
            //       �� : �ͷ��� ������, ��� �Ŵ���... �ƹ�ư�� ���̸� ã�� �� �ִ� ���� Ŭ������
            pos.y = terrain->GetHeight(pos); //������ ���� ����

            nodes.push_back(new Node(pos, nodes.size()));
            nodes.back()->Scale() = { interval.x, 50, interval.y }; // ����� ũ�� : ���μ��� = ����
                                                                    // ���� : "�ƹ�ư ���� �ȿ��� �����ϴ� �ɷδ� �� ��� ������"
            nodes.back()->UpdateWorld();

            //���̰� ���� ��� ���
            if (pos.y > 0)
            {
                //���� �ڵ� : ���� ���� ��ֹ��̴�! (TODO : �ٸ� �ó������� �ִ� ��� ������ ��)
                nodes.back()->SetState(Node::OBSTACLE);
                AddObstacle(nodes.back());
            }
        }
    }

    SetEdge(); // ���� ���� ��� ���� �����ϱ�
}

int AStar::FindCloseNode(Vector3 pos)
{
    float minDist = FLT_MAX;
    int result = -1;

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->state == Node::OBSTACLE)
            continue; //���� �ó����� : ���̰� 0���� ū ������ ���� ��� �� �Ѵ�

        float distance = Distance(pos, nodes[i]->GlobalPos());
        if (distance < minDist)
        {
            minDist = distance;
            result = i;
        }
    }

    return result;
}

int AStar::FindRandomPos(Vector3 pos, float range)
{
    vector<Node*> findNodes;

    for (Node* node : nodes) // Ŭ���� �� ���Ϳ��� ��带 ����ͼ�
    {
        //�Ÿ��� ���� �̳��� �ӽ� ���Ϳ��� ���� �߰�
        float distance = Distance(pos, node->GlobalPos());
        if (distance < range) findNodes.push_back(node);
    }

    Node* findNode = findNodes[Random(0, findNodes.size())];

    return findNode->index; // <- Ŭ���� ���̵�, ������ ���̵�, ���� �� ���� ��� �״�� ��ȯ
}

void AStar::SetEdge()
{
    UINT width = this->width + 1;

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        if (i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + 1]);
            nodes[i + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width)
        {
            nodes[i]->AddEdge(nodes[i + width]);
            nodes[i + width]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != width - 1)
        {
            nodes[i]->AddEdge(nodes[i + width + 1]);
            nodes[i + width + 1]->AddEdge(nodes[i]);
        }

        if (i < nodes.size() - width && i % width != 0)
        {
            nodes[i]->AddEdge(nodes[i + width - 1]);
            nodes[i + width - 1]->AddEdge(nodes[i]);
        }
    }
}

int AStar::GetMinNode()
{
    return heap->DeleteRoot()->index;
}

void AStar::Extend(int center, int end)
{
    for (Node::Edge* edge : nodes[center]->edges)
    {
        int index = edge->index;

        if (nodes[index]->state == Node::CLOSED) continue;
        if (nodes[index]->state == Node::OBSTACLE) continue;

        float _g = nodes[center]->g + edge->cost;
        float _h = GetDiagonalManhattanDistance(index, end);
        
        float _f = _g + _h;

        if (nodes[index]->state == Node::OPEN)
        {
            if (_f < nodes[index]->f)
            {
                nodes[index]->g = _g;
                nodes[index]->f = _f;
                nodes[index]->via = center;
            }
        }
        else if (nodes[index]->state == Node::NONE)
        {
         
            nodes[index]->g = _g;
            nodes[index]->h = _h;
            nodes[index]->f = _f;
            nodes[index]->via = center;
            nodes[index]->state = Node::OPEN;

            heap->Insert(nodes[index]);
        }
    }
}

void AStar::Reset()
{
    for (Node* node : nodes)
    {
        if (node->state != Node::OBSTACLE)
            node->state = Node::NONE;
    }

    heap->Clear();
}

float AStar::GetManhattanDistance(int start, int end)
{
    Vector3 startPos = nodes[start]->GlobalPos();
    Vector3 endPos = nodes[end]->GlobalPos();

    Vector3 distance = endPos - startPos;
    return abs(distance.x) + abs(distance.z);
}

float AStar::GetDiagonalManhattanDistance(int start, int end)
{
    Vector3 startPos = nodes[start]->GlobalPos();
    Vector3 endPos = nodes[end]->GlobalPos();

    Vector3 distance = endPos - startPos;

    float x = abs(distance.x);
    float z = abs(distance.z);

    float maxDist = max(x, z);
    float minDist = min(x, z);

    return (maxDist - minDist) + sqrt(minDist * minDist * 2);
}