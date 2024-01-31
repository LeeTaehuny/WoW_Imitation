#pragma once

class AStar
{
public:
    // AStar(class GameTileMap* map); // : 2D Ÿ�� ��� ��� ������� ����
    AStar(UINT width = 20, UINT height = 20);

    ~AStar();
    void Update();
    void Render();

    // ��尡 �� �ݶ��̴��̰� ����� Ÿ�ϸ��� �ƴϱ� ������ ��� ��ü�� ���� ��ġ�� �ʿ��ϴ�
    void SetNode() {} //�⺻��
    void SetNode(class Terrain* terrain); //�ͷ��� ��� (�ͷ��� �����ͷ� ��� ����)

    int FindCloseNode(Vector3 pos); // Ŭ���� ������ ���� �����(=���� �ǵ��� �´�) ��� ���ϱ�
    int FindRandomPos(Vector3 pos, float range); //���� ������ �������� (���ǿ� �´�) ��� ���ϱ�
    
    void GetPath(IN int start, IN int end, OUT vector<Vector3>& path); //������� V3��
    void MakeDirectionPath(IN Vector3 start, IN Vector3 end, OUT vector<Vector3>& path);

    bool IsCollisionObstacle(Vector3 start, Vector3 end);

    void AddObstacle(Collider* collider); // ��尡 ��ֹ��� ���� ����,
                                          // ���߿��� �ƹ��ų� ��ֹ��� �� �� ������ ���� ����
    

private:

    vector<Node*> nodes;
    Heap* heap; 

    vector<Collider*> obstacles; // ������ ���ǵ� ��ֹ� ����

    //�߰��� ��� ������ ���� ������
    UINT width;
    UINT height;
    Vector2 interval; //����

    //��ã�� �߰� �Լ�
    void SetEdge(); //�Ű������� Ŭ������ ���� ������ ���� ���ʿ�
    int GetMinNode();
    void Extend(int center, int end);

    void Reset();

    float GetManhattanDistance(int start, int end); // 3D���� ���� ���Ž� �ڵ�
    float GetDiagonalManhattanDistance(int start, int end);
};

