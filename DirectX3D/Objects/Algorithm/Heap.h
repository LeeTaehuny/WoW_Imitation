#pragma once

// ���� �޸� ������ �䳻�� Ŭ������ 3D �ͼ��� �ϴ� ���� �ű⼭ �ű�
// -> ��常 �ٲ�� ���� ��ü�� ũ�� �ٲ��� �ʾƵ� �� ��... (��� �����)

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

