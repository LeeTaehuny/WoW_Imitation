#pragma once
class TestDungeonScene : public Scene
{
public:
    TestDungeonScene();
    ~TestDungeonScene();

    virtual void Update() override;
    virtual void Render() override;

    virtual void PreRender() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Dungeon* dungeon;                                                    
    SphereCollider* TestSize;

    ModelAnimatorInstancing* instaning;
    CH_Base_ver2* player;
    Model* PLAYER;
};

