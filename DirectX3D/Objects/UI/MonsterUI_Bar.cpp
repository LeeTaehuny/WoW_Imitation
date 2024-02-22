#include "Framework.h"
#include "MonsterUI_Bar.h"

MonsterUI_Bar::MonsterUI_Bar()
{
	frame = new Quad(L"Textures/UI/monsterUI.png");
	frame->SetParent(this);

	hpBar = new ProgressBar(L"Textures/UI/hp_bar.png", L"Textures/UI/hp_bar_BG.png");
	hpBar->SetParent(frame);
	hpBar->Scale() = { 0.5f, 1.2f, 1.0f };
	hpBar->Pos() = { -45.0f, 18.0f };
}

MonsterUI_Bar::~MonsterUI_Bar()
{
	SAFE_DEL(frame);
	SAFE_DEL(hpBar);
}

void MonsterUI_Bar::Update()
{
	frame->UpdateWorld();
	hpBar->UpdateWorld();
	UpdateWorld();
}

void MonsterUI_Bar::PostRender()
{
	hpBar->Render();
	frame->Render();
}

void MonsterUI_Bar::SetHpPercent(float value)
{
	hpBar->SetAmount(value);
}
