#pragma once
class ParticleScene : public Scene
{
public:
    ParticleScene();
    ~ParticleScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    // 테스트용 파티클
    //ParticleSystem* particle; // 범용 파티클
    Particle* particle;         // 특수 파티클(의 범용 인터페이스)

    //-----------------------------------
    SphereCollider* collider; // 클릭용 표적
};

