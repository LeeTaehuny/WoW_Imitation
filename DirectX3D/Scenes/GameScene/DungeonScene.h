#pragma once
class DungeonScene : public Scene
{
public:
    DungeonScene();
    ~DungeonScene();

    virtual void Start() override;
    virtual void Update() override;

    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Dungeon* dungeon;

    bool isOpenGate = false;
    bool isOpenDoor = false;
    bool in_A = false;
    bool in_B = false;
    bool ClearDungeon = false;

private:
    Quad* back_;
    Quad* die_Gray;
    class Button* gaem_end;
    class Button* goTown;

    Quad* change_Scene;

    bool sound_change = false;
    bool Mounga_die = false;

    float Max_pop_time = 3.0f;
    float pop_time = Max_pop_time;

    void Change_Town();
    void Game_End();

    void Scene_Chnage();
};