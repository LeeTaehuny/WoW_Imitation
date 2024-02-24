#pragma once
class LichKingRaidScene : public Scene
{
public:
    LichKingRaidScene();
    ~LichKingRaidScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    virtual void Start() override;

private:
    BossMap* map;

};