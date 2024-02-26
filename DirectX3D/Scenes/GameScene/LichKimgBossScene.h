#pragma once
class LichKimgBossScene : public Scene
{
public:
	LichKimgBossScene();
	~LichKimgBossScene();

    virtual void Start() override;
    virtual void End() override;

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    void PL_Die_Change_Town();
    void BO_Die_Change_Town();

    void Scene_Chnage();

private:
    BossMap* map;

    CH_Base_ver2* playerData;
    MonsterBase* bossData;

    Quad* back_;
    Quad* die_Gray;
    class Button* reTry;
    class Button* goTown;

    Quad* change_Scene;

    bool pl_die = false;
    bool bo_die = false;

};