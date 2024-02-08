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

private:
    // 캐릭터 배이스
    //class CH_Base* mainPlayer;

    ModelAnimatorInstancing* pl;
    ModelAnimatorInstancing* pol;
    ModelAnimatorInstancing* pal;
    ProtectionWarrior_in* player;

    int count = 0;

    vector<ProtectionWarrior_in*> NPC;
};