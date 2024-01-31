#pragma once

class BlockManager : public Singleton<BlockManager>
{
public:
    BlockManager() = default;
    ~BlockManager();

    void Update();
    void Render();

    void CraeteBlocks(UINT width, UINT height);

    float GetHeight(const Vector3& pos) const;

    Cube* GetCollisionBlock();
    bool BuildBlock(Cube* block);

    void Push(Collider* collider);

private:
    list<Cube*> blocks;
};