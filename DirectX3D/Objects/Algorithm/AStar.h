#pragma once

class AStar
{
public:
    // AStar(class GameTileMap* map); // : 2D 타일 기반 배경 사용하지 않음
    AStar(UINT width = 20, UINT height = 20);

    ~AStar();
    void Update();
    void Render();

    // 노드가 곧 콜라이더이고 배경이 타일맵이 아니기 때문에 노드 자체가 따로 배치가 필요하다
    void SetNode() {} //기본형
    void SetNode(class Terrain* terrain); //터레인 사용 (터레인 에디터로 대용 가능)

    int FindCloseNode(Vector3 pos); // 클릭한 곳에서 가장 가까운(=가장 의도에 맞는) 노드 구하기
    int FindRandomPos(Vector3 pos, float range); //범위 내에서 무작위로 (조건에 맞는) 노드 구하기
    
    void GetPath(IN int start, IN int end, OUT vector<Vector3>& path); //결과물을 V3로
    void MakeDirectionPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path);

    bool IsCollisionObstacle(Vector3 start, Vector3 end);

    void AddObstacle(Collider* collider); // 노드가 장애물일 때도 쓰고,
                                          // 나중에는 아무거나 장애물이 될 수 있으면 적용 가능
    

private:

    vector<Node*> nodes;
    Heap* heap; 

    vector<Collider*> obstacles; // 사전에 정의된 장애물 벡터

    //추가로 배경 설정을 위한 변수들
    UINT width;
    UINT height;
    Vector2 interval; //간격

    //길찾기 추가 함수
    void SetEdge(); //매개변수는 클래스가 갖고 있으니 이제 불필요
    int GetMinNode();
    void Extend(int center, int end);

    void Reset();

    float GetManhattanDistance(int start, int end); // 3D에선 이제 레거시 코드
    float GetDiagonalManhattanDistance(int start, int end);
};

