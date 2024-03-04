#include "Framework.h"

SceneManager::~SceneManager()
{
    for (pair<string, Scene*> scene : scenes)
    {
        delete scene.second;
    }
}

void SceneManager::Update()
{
    if (curScene == nullptr) return;

    curScene->Update();
}

void SceneManager::PreRender()
{
    if (curScene == nullptr) return;

    curScene->PreRender();
}

void SceneManager::Render()
{
    if (curScene == nullptr) return;

    curScene->Render();
}

void SceneManager::PostRender()
{
    if (curScene == nullptr) return;

    curScene->PostRender();
}

void SceneManager::GUIRender()
{
    if (curScene == nullptr) return;

    curScene->GUIRender();
}

void SceneManager::Register(string key, Scene* scene)
{
    if (scenes.count(key) > 0) return;

    scenes[key] = scene;
}

void SceneManager::ChangeScene(string key)
{
    if (scenes.count(key) == 0) return;
    if (scenes[key] == curScene) return;

    curScene = scenes[key];
    curScene->Start();
}