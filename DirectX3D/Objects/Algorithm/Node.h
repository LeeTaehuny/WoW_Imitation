#pragma once

// A* 노드, 3D 호출용
// -> 1. 벡터2에서 3으로 바뀌어야 한다
// -> 2. 원래 2D도 단순한 타일은 아니었지만 (그래서 타일을 대신할 규격을 스로 만들었지만)
//       3D는 더욱더 규격이 없어서 자체 규격을 하나 끌어와서 써야 한다
//       -> 상자를 (새로운 타일을) 가져오자

class Node : public BoxCollider // <- 3D A*를 위한 새 규격(의 한 가지)
                                //    이 클래스여야 한다 x
                                //    3D에서도 다른 규격을 통해 노드를 맞춰줄 필요는 있다 o
{
public:
    friend class AStar;

    struct Edge
    {
        int index;
        float cost;
        // 엣지 구조체 안에 콜라이더가 필요 없어지면서 파생 코드 모두 생략
    };

    enum State
    {
        NONE,
        OPEN,
        CLOSED,
        USING, 
        OBSTACLE,
    };

    Node(Vector3 pos, int index); // 벡터3 필요
    ~Node();

    void Render();

    void AddEdge(Node* node);

    float GetCost() { return f; }
    void SetState(State state) { this->state = state; }

private:
    // 위치 필요없음, 콜라이더 정보 필요없음 (노드가 곧 콜라이더)

    // 인덱스, 경유지
    int index = 0;
    int via = -1;

    // 이동 비용
    float f = 0;
    float g = 0;
    float h = 0;

    //현재 이 노드의 상태
    State state = NONE;

    //인접지(들)
    vector<Edge*> edges;
};

