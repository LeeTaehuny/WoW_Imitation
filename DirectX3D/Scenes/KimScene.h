#pragma once
class KimScene : public Scene
{
public:
    KimScene();
    ~KimScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    void spawn(ModelAnimatorInstancing* pol);

    void instacning01();
    void instacning02();
    void instacning03();
    void instacning04();
    void instacning05();

private:
    // 캐릭터 배이스
    //class CH_Base* mainPlayer;

    ModelAnimatorInstancing* paladin;
    ModelAnimatorInstancing* firemage;
    ModelAnimatorInstancing* holypriest;
    ModelAnimatorInstancing* armswarrior;
    ModelAnimatorInstancing* marksmanshiphunter;
    CH_Base_ver2* player;
    int count = 0;

    MonsterBase* targetMonster;
    class SkillBase* skill;

    vector<CH_Base_ver2*> NPC;
};