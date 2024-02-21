#pragma once
#include "Scenes/Scene.h"

class TestScene : public Scene
{
public:
    TestScene();
    virtual ~TestScene() override;

    virtual void Update() override;

    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    virtual void Start() override;
    virtual void End() override;

private:
    class Shop* shop;

    int count = 0;
    ModelAnimatorInstancing* paladin;
    CH_Base_ver2* player;

    class SkillBase* skill1;
    class SkillBase* skill2;
    class SkillBase* skill3;
    class SkillBase* skill4;
    class SkillBase* skill5;
    class SkillBase* skill6;
    class SkillBase* skill7;
    class SkillBase* skill8;
    class SkillBase* skill9;
    class SkillBase* skill10;

    MonsterBase* targetMonster;

    Transform* startEdge;
    Transform* endEdge;
    Trail* trail;

    class Item* weapon;
    class StatusUI* stat;


    class QuickSlot* slot;

    ProgressBar* hpBar;
    ProgressBar* mpBar;
    Quad* HpFrame;

    class PlayerUI_Bar* p_bar;
    class MonsterUI_Bar* m_bar;
};

