#pragma once
class LichKimgBossScene : public Scene
{
public:
	LichKimgBossScene();
	~LichKimgBossScene();

    virtual void Start() override;

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    void Change_Town();
    void Game_End();

    void Scene_Chnage();

private:
    BossMap* map;

    CH_Base_ver2* playerData;
    MonsterBase* bossData;

    Quad* back_;
    Quad* die_Gray;
    class Button* gaem_end;
    class Button* goTown;

    Quad* change_Scene;

    bool Mounga_die = false;
    bool game_end = false;

    bool sound_change = false;

    // 씬채인지 화면을 띄우기 위함
    float Max_pop_time = 3.0f;
    float pop_time = Max_pop_time;

};