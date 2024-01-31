#pragma once

// A* ���, 3D ȣ���
// -> 1. ����2���� 3���� �ٲ��� �Ѵ�
// -> 2. ���� 2D�� �ܼ��� Ÿ���� �ƴϾ����� (�׷��� Ÿ���� ����� �԰��� ���� ���������)
//       3D�� ����� �԰��� ��� ��ü �԰��� �ϳ� ����ͼ� ��� �Ѵ�
//       -> ���ڸ� (���ο� Ÿ����) ��������

class Node : public BoxCollider // <- 3D A*�� ���� �� �԰�(�� �� ����)
                                //    �� Ŭ�������� �Ѵ� x
                                //    3D������ �ٸ� �԰��� ���� ��带 ������ �ʿ�� �ִ� o
{
public:
    friend class AStar;

    struct Edge
    {
        int index;
        float cost;
        // ���� ����ü �ȿ� �ݶ��̴��� �ʿ� �������鼭 �Ļ� �ڵ� ��� ����
    };

    enum State
    {
        NONE,
        OPEN,
        CLOSED,
        USING, 
        OBSTACLE,
    };

    Node(Vector3 pos, int index); // ����3 �ʿ�
    ~Node();

    void Render();

    void AddEdge(Node* node);

    float GetCost() { return f; }
    void SetState(State state) { this->state = state; }

private:
    // ��ġ �ʿ����, �ݶ��̴� ���� �ʿ���� (��尡 �� �ݶ��̴�)

    // �ε���, ������
    int index = 0;
    int via = -1;

    // �̵� ���
    float f = 0;
    float g = 0;
    float h = 0;

    //���� �� ����� ����
    State state = NONE;

    //������(��)
    vector<Edge*> edges;
};

