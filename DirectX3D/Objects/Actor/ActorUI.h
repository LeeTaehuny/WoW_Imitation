#pragma once

class ActorUI
{
public:
    ActorUI();
    ~ActorUI();

    void Update();
    void PostRender();
    void GUIRender();

    void Mining();
    void Build();

private:
    Quad* crossHair;
    Quad* quickSlot;
    Quad* iconFrame;    

    vector<Quad*> blockIcons;
    map<int, pair<int, int>> iconData;

    map<int, vector<Cube*>> blocks;

    int selectIconIndex = -1;
};