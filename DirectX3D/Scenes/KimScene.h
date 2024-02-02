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
    // 캐릭터 배이스
    CH_Base* mainPlayer;

    Collider* coll;

    Model* skel;

};