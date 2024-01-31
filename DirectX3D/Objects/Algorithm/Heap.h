#pragma once

// 힙은 메모리 구조를 흉내낸 클래스라 3D 와서도 하는 일은 거기서 거기
// -> 노드만 바뀌면 힙은 대체로 크게 바뀌지 않아도 될 듯... (적어도 헤더는)

class Heap
{
public:
    Heap();
    ~Heap();

    void Insert(Node* node);
    Node* DeleteRoot();

    void UpdateUpper(int index);
    void UpdateLower(int index);

    void Swap(int n1, int n2);

    void Clear() { heap.clear(); }
    bool Empty() { return heap.empty(); }

private:
    vector<Node*> heap;

};

