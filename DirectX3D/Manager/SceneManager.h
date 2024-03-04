#pragma once

class SceneManager : public Singleton<SceneManager>
{
private:
    friend class Singleton;

    SceneManager() = default;
    ~SceneManager();

public:
    void Update();

    void PreRender();
    void Render();
    void PostRender();
    void GUIRender();

    // 씬을 등록하기 위한 함수를 선언합니다.
    void Register(string key, Scene* scene);
    // 씬을 변경하기 위한 함수를 선언합니다.
    void ChangeScene(string key);

private:
    // 씬을 저장하기 위한 맵 컨테이너를 선언합니다.
    map<string, Scene*> scenes;
    // 현재 플레이 중인 씬을 임시로 저장하기 위한 변수를 선언합니다.
    Scene* curScene = nullptr;
};