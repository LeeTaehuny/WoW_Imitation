#include "Framework.h"

#include "Scenes/CubeScene.h"
#include "Scenes/GridScene.h"
#include "Scenes/SphereScene.h"
#include "Scenes/TerrainEditorScene.h"
#include "Scenes/TerrainScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/ModelExportScene.h"
#include "Scenes/ModelRenderScene.h"
#include "Scenes/ModelAnimationScene.h"
#include "Scenes/IntancingScene.h"
#include "Scenes/HumanScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/RenderTargetScene.h"
#include "Scenes/GBufferScene.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/AStarScene.h"
#include "Scenes/LightScene.h"
#include "Scenes/BillboardScene.h"
#include "Scenes/ParticleScene.h"
#include "Scenes/ParticleConfigScene.h"
#include "Scenes/MirrorScene.h"
#include "Scenes/WaterScene.h"
#include "Scenes/QuadTreeScene.h"
#include "Scenes/TessellationScene.h"
#include "Scenes/TerrainLODScene.h"
#include "Scenes/KimScene.h"
#include "Scenes/DevScene/TestScene.h"
#include "Scenes/MAP/MapTestScene.h"
#include "Scenes/MAP/TestDungeonScene.h"
///////////////////////////////////////////
#include "Scenes/GameScene/SelectScene.h"
#include "Scenes/GameScene/LichKingRaidScene.h"
#include "Scenes/GameScene/DungeonScene.h"
#include "Scenes/GameScene/TownScene.h"


#include "Scenes/MAP/TestExportRender.h"

GameManager::GameManager()
{
    Create();


    //SceneManager::Get()->Register("ModelExport", new ModelExportScene());
    //SceneManager::Get()->ChangeScene("ModelExport");    


    /////////////////////////////////////////////////////////////////// Choi
    // Test Scenes
    //SceneManager::Get()->Create("BossMap", new MapTestScene());
    //SceneManager::Get()->Add("BossMap");
    //SceneManager::Get()->Register("TestDungeon", new TestDungeonScene());
    //SceneManager::Get()->ChangeScene("TestDungeon");

    // ModelExport
    //SceneManager::Get()->Create("ModelExport", new ModelExportScene());
    //SceneManager::Get()->Add("ModelExport");
    //SceneManager::Get()->Register("TestExportRender", new TestExportRender());
    //SceneManager::Get()->ChangeScene("TestExportRender");

    // Terrains
    //SceneManager::Get()->Create("Terrain", new TerrainEditorScene());
    //SceneManager::Get()->Add("Terrain");
    //SceneManager::Get()->Create("Terrain", new TerrainScene());
    //SceneManager::Get()->Add("Terrain");
    //SceneManager::Get()->Create("Terrain", new TerrainLODScene());
    //SceneManager::Get()->Create("LOD", new TerrainLODScene());

    //GameScene
    
    //SceneManager::Get()->Register("BossMapScene", new BossMapScene());
    //SceneManager::Get()->ChangeScene("BossMapScene");

    ///////////////////////////////////////////////////////////////////////////
    SceneManager::Get()->Register("Select", new SelectScene());
    SceneManager::Get()->Register("Town", new TownScene());
    SceneManager::Get()->Register("DungeonScene", new DungeonScene());
    SceneManager::Get()->Register("Boss", new LichKingRaidScene());

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
    Font::Get()->RenderText(fps, { 100, WIN_HEIGHT - 10 });
    
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
