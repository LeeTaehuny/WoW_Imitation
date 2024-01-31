#pragma once

class GameScene : public Scene
{
public:

    GameScene();
    ~GameScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:

private:

    Model* background;

    Naruto* naruto;
    // + �κ� �Ŵ���, + ���� �Ŵ���

    //���� ���� ���� : WinAPI�� ����-����-ȥ�� blt�� ������ ����
    //                  ������ ���� �����ְ�, ���İ��� �����ϰ�, �ֺ� �̹����� ȥ�����ش�
    BlendState* blendState[2];

    SkyBox* skybox;

};

