#pragma once

class IntancingScene : public Scene
{
public:
    IntancingScene();
    ~IntancingScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

    ModelAnimatorInstancing* models;

    int instanceID = 0; // 현재 (선택중인) 인스턴스의 ID
    int clip = 0;       // 어떤 동작을 수행할 것인가

    int SIZE = 10;      // 여러 명 만들었을 때, 어떻게 정렬할 것인가 (정렬크기)
};

