#pragma once
#include "Scenes/Scene.h"

class SelectScene : public Scene
{
public:
	SelectScene();
	virtual ~SelectScene() override;

    virtual void Start() override;
    virtual void Update() override;

    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    // 배경 생성 함수
    void CreateBackGround();
    // 프리뷰 모델 생성 함수
    void CreatePreviewModels();
    // UI 생성 함수
    void CreateUI();
    // 조작 함수
    void Control();
    // 다음 씬 데이터 로딩용 함수
    void Loding();

// events
private:
    void OnClick_Start();

// Background & Models
private:
    // 배경
    class Quad* backGround;
    // 로딩 화면
    class Quad* loding;

    // 모델 프리뷰 전용
    class vector<ModelAnimator*> previewModels;

// UI
private:
    vector<class Quad*> icons;
    class Button* start;

// Member Variable
private:
    // 선택한 캐릭터의 인덱스를 저장하기 위한 변수
    int saveIndex;

    // 매니저 우선 로딩을 위한 판별용 변수
    bool isReady;
};

