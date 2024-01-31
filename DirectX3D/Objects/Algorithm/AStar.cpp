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
    // 시프트+우클릭하면 수동으로 장애물 지정 (타일맵 편집 대체)
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
        path.push_back(nodes[curIndex]->GlobalPos()); // 노드의 멤버변수 대신 콜라이더로서의 위치를 사용
        curIndex = nodes[curIndex]->via;
    }

    //맵 내 데이터가 아니라 아예 정점간 계산이라,
    //시작 위치 = 캐릭터나 주어진 위치를 그대로 대입해도 문제x
    //path.push_back(nodes[start]->GlobalPos());
}

void AStar::MakeDirectionPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path)
{
    //이 함수의 목적 : 1. 시작점에서 종점까지 가는 직선 거리 중, 길을 빼버리고 남은 장애물의 거리 도출
    //                2. (1.에서 간접 도출) 시작점에서, 종점을 향해 가면 장애물을 안 만나고 갈 수 있는 가장 먼 거리
    //                ...중 하나를 얻기 위함
    
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
    Ray ray(start, (end - start).GetNormalized()); //시작점에서, 끝을 향하는 광선 준비

    float distance = Distance(start, end); //거리 내기

    Contact contact; // 접점정보 준비

    for (Collider* obstacle : obstacles)
    {
        if (obstacle->IsRayCollision(ray, &contact))
        {
            if (contact.distance < distance) //접점까지의 거리가 종점까지의 거리보다 짧으면
            {
                return true; //직선으로 가는 중에 장애물이 있었음
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
    //터레인 (혹은 다른 클래스라도 가능) 받아와서 해당 위치에 노드 배치하기

    //지형이 기준이므로 여기서는 2차원인 것처럼 이해를 해도 될 것
    //Vector2 mapSize = terrain->GetMaterial()->GetDiffuseMap()->GetSize();
    //TODO : 지형이 이후 크기가 따로 지정이 가능하다면 여기서도 크기를 불러와야 한다
    //       예 : 터레인 에디터... (터레인 클래스도 이후 크기가 바뀐다면 GetSize 필요)
    //       * 요점은 매개변수로 받을 지형 담당 클래스가 GetSize를 잘 줄 수 있어야 한다

    Vector2 mapSize = terrain->GetSize(); // 지형 크기 반영됨

    //배치간격 구하기
    interval.x = mapSize.x / width; //맵 크기를 길찾기의 가로로 나누기
    interval.y = mapSize.y / height;

    nodes.reserve((width + 1) * (height + 1)); // +1 : 크기 연산과 벡터 순번 연산 오차

    for (UINT z = 0; z <= height; ++z)
    {
        for (UINT x = 0; x <= width; ++x)
        {
            //배치간격과 가로세로 좌표를 반영해서 위치 내기
            Vector3 pos = Vector3(x * interval.x, 0, z * interval.y);
            //pos.y = 0; // 기준값 0 : 기본값
            //TODO : 기준값이 바뀌면 위 코드 수정할 것
            //       예 : 터레인 에디터, 블록 매니저... 아무튼간 높이를 찾을 수 있는 지형 클래스들
            pos.y = terrain->GetHeight(pos); //지형에 의한 높이

            nodes.push_back(new Node(pos, nodes.size()));
            nodes.back()->Scale() = { interval.x, 50, interval.y }; // 노드의 크기 : 가로세로 = 간격
                                                                    // 높이 : "아무튼 지형 안에서 점프하는 걸로는 못 벗어날 정도로"
            nodes.back()->UpdateWorld();

            //높이가 높은 경우 대비
            if (pos.y > 0)
            {
                //샘플 코드 : 높은 곳은 장애물이다! (TODO : 다른 시나리오가 있는 경우 수정할 것)
                nodes.back()->SetState(Node::OBSTACLE);
                AddObstacle(nodes.back());
            }
        }
    }

    SetEdge(); // 인접 노드와 경로 관계 연결하기
}

int AStar::FindCloseNode(Vector3 pos)
{
    float minDist = FLT_MAX;
    int result = -1;

    for (UINT i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->state == Node::OBSTACLE)
            continue; //샘플 시나리오 : 높이가 0보다 큰 지형의 노드는 취급 안 한다

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

    for (Node* node : nodes) // 클래스 내 벡터에서 노드를 끌어와서
    {
        //거리가 범위 이내면 임시 벡터에도 같이 추가
        float distance = Distance(pos, node->GlobalPos());
        if (distance < range) findNodes.push_back(node);
    }

    Node* findNode = findNodes[Random(0, findNodes.size())];

    return findNode->index; // <- 클릭한 곳이든, 도출한 곳이든, 범위 내 랜덤 노드 그대로 반환
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