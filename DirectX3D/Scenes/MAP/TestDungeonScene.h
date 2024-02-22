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
   
    ModelAnimatorInstancing* instaning;
    CH_Base_ver2* player;
    Model* PLAYER;

    vector<SphereCollider*> TestMonsterSpawnPos_A;
    vector<SphereCollider*> TestMonsterSpawnPos_B;
    //vector<Model*> TestMonsterSpawnPos_A;
    //vector<Model*> TestMonsterSpawnPos_B;

    //TerrainLOD* terrain;
};

