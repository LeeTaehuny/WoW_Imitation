#include "Framework.h"

#include "Scenes/TerrainEditorScene.h"
#include "Scenes/ModelExportScene.h"
#include "Scenes/ModelRenderScene.h"
#include "Scenes/ParticleConfigScene.h"
///////////////////////////////////////////
#include "Scenes/GameScene/SelectScene.h"
#include "Scenes/GameScene/LichKimgBossScene.h"
#include "Scenes/GameScene/DungeonScene.h"
#include "Scenes/GameScene/TownScene.h"

GameManager::GameManager()
{
    Create();

    //SceneManager::Get()->Register("ModelExport", new ModelExportScene());
    //SceneManager::Get()->ChangeScene("ModelExport");    

    ///////////////////////////////////////////////////////////////////////////
    SceneManager::Get()->Register("Select", new SelectScene());
    SceneManager::Get()->Register("Town", new TownScene());
    SceneManager::Get()->Register("DungeonScene", new DungeonScene());
    SceneManager::Get()->Register("Boss", new LichKimgBossScene());
    
    SceneManager::Get()->ChangeScene("Select");
}

GameManager::~GameManager()
{
    Delete();
}

void GameManager::Update()
{
    Keyboard::Get()->Update();
    Timer::Get()->Update();
    Audio::Get()->Update();
    SceneManager::Get()->Update();

    Environment::Get()->Update();
}

void GameManager::Render()
{
    
    
    Device::Get()->Clear();
    Font::Get()->GetDC()->BeginDraw();

    Environment::Get()->PostSet();
    SceneManager::Get()->PreRender();
    
    Environment::Get()->Set();    
    SceneManager::Get()->Render();
    
    Environment::Get()->PostSet();
    SceneManager::Get()->PostRender();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
    //Font::Get()->RenderText(fps, { 100, WIN_HEIGHT - 10 });
    
    static bool isActive = true;

    if (isActive)
    {
        ImGui::Begin("Inspector", &isActive);
        Environment::Get()->GUIRender();
        SceneManager::Get()->GUIRender();
        ImGui::End();
    }    

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    
    Font::Get()->GetDC()->EndDraw();

    Device::Get()->Present();
}

void GameManager::Create()
{
    Keyboard::Get();
    Timer::Get();
    Device::Get();
    Environment::Get();
    Observer::Get();
    
    Font::Get()->AddColor("White", 1, 1, 1);
    Font::Get()->AddStyle("Default", L"배달의민족 주아");
    
    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");

    Texture::Add(L"Textures/Color/White.png");
    
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
    Keyboard::Delete();
    Timer::Delete();
    Device::Delete();
    Shader::Delete();
    Texture::Delete();
    Environment::Delete();    
    Observer::Delete();
    Font::Delete();
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    
    ImGui::DestroyContext();
}
