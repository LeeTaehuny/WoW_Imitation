#include "Framework.h"
#include "TownScene.h"
#include "Objects/Skills/SkillManager.h"
#include "Objects/Shop/Shop.h"

TownScene::TownScene()
{
	terrain = new Terrain();
    terrain->UpdateWorld();
	shop = new Shop();

    // 나무 생성
    CreateBillboard();
}

TownScene::~TownScene()
{
}

void TownScene::Start()
{
	CH->GetPlayerData()->Pos() = Vector3(210.0f, 0.0f, 165.0f);
	CH->GetPlayerData()->Rot() = Vector3(0.0f, 7.3f, 0.0f);
    CH->GetPlayerData()->SetTerrain(terrain);
	SKILL->Init(CH->GetPlayerData());
	CAM->SetTarget(CH->GetPlayerData());

    MONSTER->SpawnScarecrow(Vector3(80.0f, 0.0f, 185.0f));
    MONSTER->SpawnScarecrow(Vector3(85.0f, 0.0f, 175.0f));
    MONSTER->SpawnScarecrow(Vector3(65.0f, 0.0f, 180.0f));

	shop->Pos() = Vector3(167, 1.0f, 167);
	shop->UpdateWorld();
}

void TownScene::Update()
{
    int height = terrain->GetHeight(CH->GetPlayerData()->Pos());
    CH->GetPlayerData()->SetHeight(height);
   
	CH->Update();
	SKILL->Update();

    MONSTER->Update();

	shop->Update();
}

void TownScene::PreRender()
{
}

void TownScene::Render()
{
	terrain->Render();
	shop->Render();
	CH->Render();

    MONSTER->Render();
    RenderBillboard();
}

void TownScene::PostRender()
{
	SKILL->PostRender();
	shop->UIRender();
	CH->PostRender();
    MONSTER->PostRender();
}

void TownScene::GUIRender()
{

}

void TownScene::CreateBillboard()
{
    material = new Material(L"Geometry/Billboard.hlsl");
    material->SetDiffuseMap(L"Textures/Landscape/Tree.png");

    geometryShader = Shader::AddGS(L"Geometry/Billboard.hlsl");

    vertices.resize(230);
    FOR(230)
    {
        if (i >= 0 && i < 30)
        {
            vertices[i].uv.x = Random(5.0f, 12.0f);
            vertices[i].uv.y = vertices[i].uv.x;

            vertices[i].pos.x = Random(0.0f, 30.0f);
            vertices[i].pos.z = Random(0.0f, 256.0f);
            vertices[i].pos.y = terrain->GetHeight(Vector3(vertices[i].pos.x, 0.0f, vertices[i].pos.z)) + vertices[i].uv.y / 2;
        }
        else if (i >= 30 && i < 60)
        {
            vertices[i].uv.x = Random(5.0f, 12.0f);
            vertices[i].uv.y = vertices[i].uv.x;

            vertices[i].pos.x = Random(30.0f, 256.0f);
            vertices[i].pos.z = Random(0.0f, 30.0f);
            vertices[i].pos.y = terrain->GetHeight(Vector3(vertices[i].pos.x, 0.0f, vertices[i].pos.z)) + vertices[i].uv.y / 2;
        }
        else if (i >= 60 && i < 90)
        {
            vertices[i].uv.x = Random(4.0f, 8.0f);
            vertices[i].uv.y = vertices[i].uv.x;

            vertices[i].pos.x = Random(130.0f, 256.0f);
            vertices[i].pos.z = Random(30.0f, 80.0f);
            vertices[i].pos.y = terrain->GetHeight(Vector3(vertices[i].pos.x, 0.0f, vertices[i].pos.z)) + vertices[i].uv.y / 2;
        }
        else if (i >= 90 && i < 110)
        {
            vertices[i].uv.x = Random(4.0f, 8.0f);
            vertices[i].uv.y = vertices[i].uv.x;

            vertices[i].pos.x = Random(150.0f, 256.0f);
            vertices[i].pos.z = Random(80.0f, 120.0f);
            vertices[i].pos.y = terrain->GetHeight(Vector3(vertices[i].pos.x, 0.0f, vertices[i].pos.z)) + vertices[i].uv.y / 2;
        }
        else if (i >= 110 && i < 130)
        {
            vertices[i].uv.x = Random(4.0f, 6.0f);
            vertices[i].uv.y = vertices[i].uv.x;

            vertices[i].pos.x = Random(180.0f, 256.0f);
            vertices[i].pos.z = Random(120.0f, 140.0f);
            vertices[i].pos.y = terrain->GetHeight(Vector3(vertices[i].pos.x, 0.0f, vertices[i].pos.z)) + vertices[i].uv.y / 2;
        }
        else if (i >= 130 && i < 150)
        {
            vertices[i].uv.x = Random(4.0f, 8.0f);
            vertices[i].uv.y = vertices[i].uv.x;

            vertices[i].pos.x = Random(220.0f, 256.0f);
            vertices[i].pos.z = Random(140.0f, 256.0f);
            vertices[i].pos.y = terrain->GetHeight(Vector3(vertices[i].pos.x, 0.0f, vertices[i].pos.z)) + vertices[i].uv.y / 2;
        }
        else if (i >= 150 && i < 190)
        {
            vertices[i].uv.x = Random(6.0f, 10.0f);
            vertices[i].uv.y = vertices[i].uv.x;

            vertices[i].pos.x = Random(30.0f, 256.0f);
            vertices[i].pos.z = Random(220.0f, 256.0f);
            vertices[i].pos.y = terrain->GetHeight(Vector3(vertices[i].pos.x, 0.0f, vertices[i].pos.z)) + vertices[i].uv.y / 2;
        }
        else if (i >= 190 && i < 210)
        {
            vertices[i].uv.x = Random(4.0f, 8.0f);
            vertices[i].uv.y = vertices[i].uv.x;

            vertices[i].pos.x = Random(30.0f, 210.0f);
            vertices[i].pos.z = Random(170.0f, 220.0f);
            vertices[i].pos.y = terrain->GetHeight(Vector3(vertices[i].pos.x, 0.0f, vertices[i].pos.z)) + vertices[i].uv.y / 2;
        }
        else if (i >= 210 && i < 230)
        {
            vertices[i].uv.x = Random(5.0f, 12.0f);
            vertices[i].uv.y = vertices[i].uv.x;

            vertices[i].pos.x = Random(30.0f, 70.0f);
            vertices[i].pos.z = Random(80.0f, 150.0f);
            vertices[i].pos.y = terrain->GetHeight(Vector3(vertices[i].pos.x, 0.0f, vertices[i].pos.z)) + vertices[i].uv.y / 2;
        }

    }
    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexUV), 230);

    FOR(2) blendState[i] = new BlendState();
    FOR(2) depthState[i] = new DepthStencilState();

    blendState[1]->Alpha(true);
    blendState[1]->AlphaToCoverage(true);
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL);
}

void TownScene::RenderBillboard()
{
    blendState[1]->SetState();
    depthState[1]->SetState();

    vertexBuffer->Set(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);

    material->Set();

    geometryShader->Set();

    DC->Draw(250, 0);

    DC->GSSetShader(nullptr, nullptr, 0);

    blendState[0]->SetState();
    depthState[0]->SetState();
}
