#include "Framework.h"
#include "PlayerUI_Bar.h"

PlayerUI_Bar::PlayerUI_Bar(wstring IconImageFile)
{
	frame = new Quad(L"Textures/UI/playerUI.png");
	frame->SetParent(this);

	icon = new Quad(IconImageFile);
	icon->SetParent(frame);
	icon->Scale() *= 0.3f;
	icon->Pos() = { -62.0f, 20.0f };

	hpBar = new ProgressBar(L"Textures/UI/hp_bar.png", L"Textures/UI/hp_bar_BG.png");
	hpBar->SetParent(frame);
	hpBar->Scale() = { 0.4f, 1.0f, 1.0f };
	hpBar->Pos() = { 30.0f, 28.0f };

	mpBar = new ProgressBar(L"Textures/UI/mp_bar.png", L"Textures/UI/hp_bar_BG.png");
	mpBar->SetParent(frame);
	mpBar->Scale() = { 0.4f, 0.5f, 1.0f };
	mpBar->Pos() = { 30.0f, 13.0f };
}

PlayerUI_Bar::~PlayerUI_Bar()
{
	SAFE_DEL(frame);
	SAFE_DEL(hpBar);
	SAFE_DEL(mpBar);
}

void PlayerUI_Bar::Update()
{
	hpBar->UpdateWorld();
	mpBar->UpdateWorld();
	icon->UpdateWorld();
	frame->UpdateWorld();
	UpdateWorld();
}

void PlayerUI_Bar::PostRender()
{
	hpBar->Render();
	mpBar->Render();
	icon->Render();
	frame->Render();
}

void PlayerUI_Bar::SetHpPercent(float value)
{
	hpBar->SetAmount(value);
}

void PlayerUI_Bar::SetMpPercent(float value)
{
	mpBar->SetAmount(value);
}
