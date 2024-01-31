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

    int instanceID = 0; // ���� (��������) �ν��Ͻ��� ID
    int clip = 0;       // � ������ ������ ���ΰ�

    int SIZE = 10;      // ���� �� ������� ��, ��� ������ ���ΰ� (����ũ��)
};

