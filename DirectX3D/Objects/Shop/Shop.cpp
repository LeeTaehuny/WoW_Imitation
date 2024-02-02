#include "Framework.h"
#include "Shop.h"
#include "Objects/Item/Item.h"
#include "Objects/Inventory/Slot.h"

Shop::Shop()
{
	// 모델 설정
	{
		shop = new Model("Shop");
		trader = new Model("Trader");

		shop->SetParent(this);
		shop->GetMaterials()[0]->SetShader(L"Light/ItemLight.hlsl");
		shop->GetMaterials()[1]->SetShader(L"Light/ItemLight.hlsl");
		shop->Scale() *= 0.5f;

		trader->SetParent(this);
		trader->GetMaterials()[0]->SetShader(L"Light/ItemLight.hlsl");
	}
	
	// RS 설정 (shop 전용)
	{
		FOR(2) rs[i] = new RasterizerState();
		rs[1]->CullMode(D3D11_CULL_NONE);
	}

	// UI 설정
	shopFrame = new Slot(L"Textures/UI/shop_frame.png", SlotType::Inventory_Frame);

	shopFrame->Scale() *= 1.75f;
	shopFrame->Pos() = { CENTER_X * 0.5f, CENTER_Y, 1.0f };
}

Shop::~Shop()
{
	SAFE_DEL(shop);
	SAFE_DEL(trader);
	SAFE_DEL(rs[1]);
	SAFE_DEL(rs[2]);
	SAFE_DEL(shopFrame);
}

void Shop::Update()
{
	shopFrame->Update();

	shop->UpdateWorld();
	trader->UpdateWorld();
}

void Shop::Render()
{
	rs[1]->SetState();
	shop->Render();
	rs[0]->SetState();

	trader->Render();
}

void Shop::UIRender()
{
	shopFrame->Render();
}

void Shop::GUIRender()
{
}
