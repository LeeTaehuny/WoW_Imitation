#include "Framework.h"

BlockManager::~BlockManager()
{
    for (Cube* block : blocks)
        delete block;

    blocks.clear();   
   
}

void BlockManager::Update()
{
    for (Cube* block : blocks)
        block->Update();
}

void BlockManager::Render()
{
    for (Cube* block : blocks)
        block->Render();
}

void BlockManager::CraeteBlocks(UINT width, UINT height)
{
    vector<wstring> textures(5);

    for (UINT i = 0; i < 5; i++)
    {
        textures[i] = L"Textures/Block/block" + to_wstring(i) + L".png";         
    }

    for (UINT z = 0; z < height; z++)
    {
        for (UINT x = 0; x < width; x++)
        {
            Vector3 pos = { (float)x, 0, (float)z };

            wstring file = textures[Random(0, textures.size())];

            Cube* block = new Cube();
            block->GetMaterial()->SetDiffuseMap(file);
            block->Pos() = pos;
            block->Update();

            blocks.push_back(block);
        }
    }
}

float BlockManager::GetHeight(const Vector3& pos) const
{
    Ray ray(pos, Vector3::Down());
    Contact contact;

    float maxHeight = 0.0f;

    for (Cube* block : blocks)
    {        
        if (block->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.hitPoint.y > maxHeight)
                maxHeight = contact.hitPoint.y;
        }
    }

    return maxHeight;
}

Cube* BlockManager::GetCollisionBlock()
{
    Ray ray = CAM->ScreenPointToRay(Vector3(CENTER_X, CENTER_Y));

    float minDistance = FLT_MAX;
    Contact contact;
    
    list<Cube*>::iterator iter = blocks.begin();
    list<Cube*>::iterator collisionBlock = blocks.end();    

    for ( ; iter != blocks.end() ; iter++)
    {        
        if ((*iter)->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance)
            {
                minDistance = contact.distance;
                collisionBlock = iter;                
            }
        }
    }

    if (collisionBlock != blocks.end())
    {        
        Cube* block = *collisionBlock;
        blocks.erase(collisionBlock);
        return block;
    }
    else
    {
        return nullptr;
    }
    
}

bool BlockManager::BuildBlock(Cube* block)
{
    Ray ray = CAM->ScreenPointToRay(Vector3(CENTER_X, CENTER_Y));

    float minDistance = FLT_MAX;
    Vector3 hitPoint;
    Contact contact;

    list<Cube*>::iterator iter = blocks.begin();
    Cube* collisionBlock = nullptr;

    for (; iter != blocks.end(); iter++)
    {
        if ((*iter)->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance)
            {
                minDistance = contact.distance;
                hitPoint = contact.hitPoint;
                collisionBlock = *iter;
            }
        }
    }

    if (collisionBlock == nullptr) return false;

    Vector3 dir = hitPoint - collisionBlock->GlobalPos();
    
    int maxIndex = 0;
    float maxValue = 0.0f;

    for (int i = 0; i < 3; i++)
    {
        if (abs(dir[i]) > maxValue)
        {
            maxIndex = i;
            maxValue = abs(dir[i]);
        }
    }

    switch (maxIndex)
    {
    case 0:
        dir.x = dir.x > 0 ? 1.0f : -1.0f;
        dir.y = 0;
        dir.z = 0;
        break;
    case 1:
        dir.y = dir.y > 0 ? 1.0f : -1.0f;
        dir.x = 0;
        dir.z = 0;
        break;
    case 2:
        dir.z = dir.z > 0 ? 1.0f : -1.0f;
        dir.y = 0;
        dir.x = 0;
        break;
    }

    block->SetActive(true);
    block->Pos() = collisionBlock->GlobalPos() + dir;
    block->Update();

    blocks.push_back(block);

    return true;
}

void BlockManager::Push(Collider* collider)
{
    Cube* collisionBlock = nullptr;

    for (Cube* block : blocks)
    {
        if (block->GetCollider()->IsCollision(collider))
        {
            collisionBlock = block;
            
            Vector3 dir = collider->GlobalPos() - collisionBlock->GlobalPos();

            int maxIndex = 0;
            float maxValue = 0.0f;

            for (int i = 0; i < 3; i++)
            {
                if (abs(dir[i]) > maxValue)
                {
                    maxIndex = i;
                    maxValue = abs(dir[i]);
                }
            }

            switch (maxIndex)
            {
            case 0:
                dir.x = dir.x > 0 ? 1.0f : -1.0f;
                dir.y = 0;
                dir.z = 0;
                break;
            case 1:
                dir.y = dir.y > 0 ? 1.0f : -1.0f;
                dir.x = 0;
                dir.z = 0;
                break;
            case 2:
                dir.z = dir.z > 0 ? 1.0f : -1.0f;
                dir.y = 0;
                dir.x = 0;
                break;
            }

            if (NearlyEqual(dir.y, 1.0f)) continue;

            collider->GetParent()->Pos() += dir * 50.0f * DELTA;
        }
    }      
}
