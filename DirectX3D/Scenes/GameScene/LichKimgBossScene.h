#pragma once
class LichKimgBossScene : public Scene
{
public:
	LichKimgBossScene();
	~LichKimgBossScene();

    virtual void Start() override;

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    BossMap* map;

};