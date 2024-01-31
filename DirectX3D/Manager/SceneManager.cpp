#include "Framework.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    //for (pair<string, Scene*> scene : scenes)
    for (auto scene : scenes)
        delete scene.second;
}

void SceneManager::Update()
{
    for (Scene* scene : curScenes)
        scene->Update();
}

void SceneManager::PreRender()
{
    for (Scene* scene : curScenes)
        scene->PreRender();
}

void SceneManager::Render()
{
    for (Scene* scene : curScenes)
        scene->Render();
}

void SceneManager::PostRender()
{
    for (Scene* scene : curScenes)
        scene->PostRender();
}

void SceneManager::GUIRender()
{
    for (Scene* scene : curScenes)
        scene->GUIRender();
}

void SceneManager::Create(string key, Scene* scene)
{
    if (scenes.count(key) > 0)
        return;

    scenes[key] = scene;
}

Scene* SceneManager::Add(string key)
{
    if (scenes.count(key) == 0)
        return nullptr;

    list<Scene*>::iterator findScene = find(curScenes.begin(), curScenes.end(), scenes[key]);

    if (findScene != curScenes.end())
        return  scenes[key];

    curScenes.push_back(scenes[key]);
    curScenes.back()->Start();

    return scenes[key];
}

void SceneManager::Remove(string key)
{
    if (scenes.count(key) == 0)
        return;

    list<Scene*>::iterator findScene = find(curScenes.begin(), curScenes.end(), scenes[key]);

    if (findScene == curScenes.end())
        return;

    scenes[key]->End();
    curScenes.erase(findScene);
}
