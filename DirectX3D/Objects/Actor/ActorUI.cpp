#include "Framework.h"

ActorUI::ActorUI()
{
    crossHair = new Quad(L"Textures/UI/cursor.png");
    crossHair->Pos() = { CENTER_X, CENTER_Y, 0 };
    crossHair->UpdateWorld();

    quickSlot = new Quad(L"Textures/UI/QuickSlot.png");
    quickSlot->SetTag("QuickSlot");
    quickSlot->Load();   
    quickSlot->UpdateWorld();

    iconFrame = new Quad(L"Textures/UI/IconFrame.png");  
    iconFrame->Scale() *= 0.7f;
    iconFrame->SetActive(false);

    for (int i = 0; i < 5; i++)
    {
        wstring file = L"Textures/Block/BlockIcon" + to_wstring(i) + L".png";
        Quad* blockIcon = new Quad(file);
        blockIcon->Scale() *= 0.1f;
        blockIcon->SetParent(quickSlot);
        //blockIcon->SetActive(false);
        blockIcon->SetTag("Icon" + to_string(i));
        
        blockIcons.push_back(blockIcon);
    }
}

ActorUI::~ActorUI()
{
    delete crossHair;
    delete quickSlot;
    delete iconFrame;

    for (Quad* blockIcon : blockIcons)
        delete blockIcon;
}

void ActorUI::Update()
{   
    if (KEY_DOWN('1'))
    {
        if (iconData[0].second > 0)
            selectIconIndex = 0;
    }
    if (KEY_DOWN('2'))
    {
        if (iconData[1].second > 0)
            selectIconIndex = 1;
    }
    if (KEY_DOWN('3'))
    {
        if (iconData[2].second > 0)
            selectIconIndex = 2;
    }
    if (KEY_DOWN('4'))
    {
        if (iconData[3].second > 0)
            selectIconIndex = 3;
    }
    if (KEY_DOWN('5'))
    {
        if (iconData[4].second > 0)
            selectIconIndex = 4;
    }   
}

void ActorUI::PostRender()
{
    crossHair->Render();
    quickSlot->Render();
        
    for (int i = 0 ; i < 5 ; i++)
    {
        Vector3 pos;
        pos.x = -80 + i * 20;

        if (iconData[i].second)
        {
            Quad* icon = blockIcons[iconData[i].first];
            icon->Pos() = pos;
            icon->UpdateWorld();
            icon->Render();

            string str = to_string(iconData[i].second);            

            Vector3 temp = icon->GlobalPos();

            Font::Get()->RenderText(str, {temp.x, temp.y});

            if (i == selectIconIndex)
            {
                iconFrame->SetActive(true);
                iconFrame->Pos() = icon->GlobalPos();
                iconFrame->UpdateWorld();
                iconFrame->Render();
            }
            else
            {
                iconFrame->SetActive(false);
            }
        }
    }    
}

void ActorUI::GUIRender()
{
    //quickSlot->GUIRender();
    //for (Quad* blockIcon : blockIcons)
        //blockIcon->GUIRender();
    iconFrame->GUIRender();
}

void ActorUI::Mining()
{
    Cube* block = BlockManager::Get()->GetCollisionBlock();

    if (block == nullptr)
        return;

    wstring file = block->GetMaterial()->GetDiffuseMap()->GetFile();

    int temp = file.find_last_of('.');
    file = file.substr(temp - 1, 1);
    int index = stoi(file);

    if (blocks[index].size() == 0)
    {
        for (int i = 0 ; i < 5 ; i++)
        {
            if (iconData[i].second == 0)
            {
                iconData[i].first = index;
                iconData[i].second++;
                break;
            }
        }
    }
    else
    {
        for (auto& data : iconData)
        {
            if (data.second.first == index)
            {
                data.second.second++;
                break;
            }
        }
    }

    blocks[index].push_back(block);
}

void ActorUI::Build()
{
    if (selectIconIndex < 0) return;

    Cube* block = blocks[iconData[selectIconIndex].first].back();    

    if (BlockManager::Get()->BuildBlock(block))
    {
        blocks[iconData[selectIconIndex].first].pop_back();
        iconData[selectIconIndex].second--;

        if (iconData[selectIconIndex].second == 0)
            selectIconIndex = -1;
    }    
}
