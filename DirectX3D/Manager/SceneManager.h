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

    // ���� ����ϱ� ���� �Լ��� �����մϴ�.
    void Register(string key, Scene* scene);
    // ���� �����ϱ� ���� �Լ��� �����մϴ�.
    void ChangeScene(string key);

private:
    // ���� �����ϱ� ���� �� �����̳ʸ� �����մϴ�.
    map<string, Scene*> scenes;
    // ���� �÷��� ���� ���� �ӽ÷� �����ϱ� ���� ������ �����մϴ�.
    Scene* curScene = nullptr;
};