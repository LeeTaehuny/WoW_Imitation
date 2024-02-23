#pragma once
class MapTestScene : public Scene
{
public:
    MapTestScene();
    ~MapTestScene();

    virtual void Update() override; 
    virtual void Render() override;

    virtual void PreRender() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    BossMap* bossmap;
    SphereCollider* Test;

    ModelAnimatorInstancing* instaning;
    CH_Base_ver2* player;
    Model* PLAYER;
};

