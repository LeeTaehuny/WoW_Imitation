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
    // + 로봇 매니저, + 쿠나이 매니저

    //블렌드 상태 설정 : WinAPI의 투명-알파-혼합 blt와 유사한 역할
    //                  지정된 색을 지워주고, 알파값을 적용하고, 주변 이미지와 혼합해준다
    BlendState* blendState[2];

    SkyBox* skybox;

};

