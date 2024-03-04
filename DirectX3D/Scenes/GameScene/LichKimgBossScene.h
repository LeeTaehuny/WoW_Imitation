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
    // 마을로 돌아가기 버튼이 눌렸을때 실행되는 함수
    void Change_Town();
    // 게임 엔드 버튼이 눌렸을때 실행
    void Game_End();

    // 씬체인지에 사용되는 함수
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

    // 캐릭터가 먼저 죽었을때
    bool pldie_first = false;
    // 보스가 먼저 죽었을때
    bool bodie_first = false;

};