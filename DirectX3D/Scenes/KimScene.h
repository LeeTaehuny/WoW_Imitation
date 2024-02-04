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

private:
    // ĳ���� ���̽�
    CH_Base* mainPlayer;

    vector<Collider*> coll;
    Collider* dlatl;

    //Model* skel;
    ModelAnimator* skel;

    int value = 0;

    SkillBase* skill;
};