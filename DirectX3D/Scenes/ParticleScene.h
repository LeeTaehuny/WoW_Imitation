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
    // �׽�Ʈ�� ��ƼŬ
    //ParticleSystem* particle; // ���� ��ƼŬ
    Particle* particle;         // Ư�� ��ƼŬ(�� ���� �������̽�)

    //-----------------------------------
    SphereCollider* collider; // Ŭ���� ǥ��
};

