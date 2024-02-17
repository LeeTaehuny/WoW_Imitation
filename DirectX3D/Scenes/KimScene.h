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

    MonsterBase* targetMonster;
    CH_Base_ver2* targetNPC;

    SkillBase* skills;

    ParticleSystem* particle;
};