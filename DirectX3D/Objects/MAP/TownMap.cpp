#include "Framework.h"
#include "TownMap.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Shop/Guild.h"

TownMap::TownMap()
{
    Init();
}

TownMap::~TownMap()
{
    SAFE_DEL(terrain);
    SAFE_DEL(shop);
    SAFE_DEL(portal);
    SAFE_DEL(sky);
    SAFE_DEL(portalImage);
    SAFE_DEL(collider);

    SAFE_DEL(blendState[0]);
    SAFE_DEL(blendState[1]);
    SAFE_DEL(material);
    SAFE_DEL(vertexBuffer);
    SAFE_DEL(depthState[0]);
    SAFE_DEL(depthState[1]);
}

void TownMap::Init()
{
    terrain = new Terrain();
    terrain->UpdateWorld();
    shop = new Shop();
    portal = new Model("TownPortal");
    portal->SetShader(L"Light/ItemLight.hlsl");
    sky = new SkyBox(L"Textures/Landscape/BlueSky.dds");
    portalImage = new Quad(Vector2(60, 60));
    portalImage->GetMaterial()->SetDiffuseMap(L"Textures/Etc/portal.png");
    collider = new BoxCollider(Vector3(60, 60, 3));
    guild = new Guild();

    CreateBillboard();

    int height = terrain->GetHeight(Vector3(80.0f, 0.0f, 185.0f));
    portal->Scale() *= 0.5f;
    portal->Pos() = Vector3(95.0f, height, 78.0f);
    portal->Rot() = Vector3(0.0f, XM_PI / 6, 0.0f);
    portalImage->Pos() = Vector3(95.0f, height, 77.0f);
    portalImage->Rot() = Vector3(XM_2PI / 2, XM_PI / 6, XM_2PI / 2);
    collider->Pos() = portalImage->Pos();
    collider->Rot() = portalImage->Rot();
    shop->Pos() = Vector3(167, height, 167);
    shop->UpdateWorld();
    guild->Pos() = Vector3(135, height, 165);
    guild->UpdateWorld();
}

void TownMap::Update()
{
    shop->Update();
    guild->Update();
    portal->UpdateWorld();
    portalImage->UpdateWorld();

    UpdateWorld();
    collider->UpdateWorld();
}

void TownMap::PreRender()
{
}

void TownMap::Render()
{
    sky->Render();

    terrain->Render();
    shop->Render();
    guild->Render();

    portal->Render();

    collider->Render();

    RenderBillboard();

    blendState[1]->SetState();
    portalImage->Render();
    blendState[0]->SetState();
}

void TownMap::PostRender()
{
    shop->UIRender();
    guild->UIRender();
}

void TownMap::GUIRender()
{
    collider->GUIRender();
}

void TownMap::CreateBillboard()
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

void TownMap::RenderBillboard()
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
