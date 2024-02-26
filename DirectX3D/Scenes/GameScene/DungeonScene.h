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

    vector<Vector3> TestMonsterSpawnPos_A;
    vector<Vector3> TestMonsterSpawnPos_B;
};

