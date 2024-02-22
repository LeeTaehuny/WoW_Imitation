#include "Framework.h"
#include "PartyUI_Bar.h"

PartyUI_Bar::PartyUI_Bar()
{
}

PartyUI_Bar::~PartyUI_Bar()
{
}

void PartyUI_Bar::Update()
{
	for (ProgressBar* bar : hpBars)
	{
		bar->UpdateWorld();
	}

	UpdateWorld();
}

void PartyUI_Bar::PostRender()
{
	int idx = 1;
	for (ProgressBar* bar : hpBars)
	{
		bar->Render();

		Font::Get()->RenderText(CH->GetCharcterData()[idx]->GetTag(), Vector2(bar->GlobalPos().x - 60.0f, bar->GlobalPos().y + 2.0f));

		idx++;
	}
}

void PartyUI_Bar::AddPlayer(int index)
{
	// 해당 캐릭터 타입에 따라 hp바 생성
	switch (CH->GetCharcterData()[index]->GetProfessionType())
	{
	case ProfessionType::ArmsWarrior:
		hpBars.push_back(new ProgressBar(L"Textures/UI/A_hpBar.png", L"Textures/UI/hp_bar_BG.png"));
		hpBars[hpBars.size()-1]->SetParent(this);
		hpBars[hpBars.size() - 1]->Scale() = Vector3(0.5f, 1.55f, 1.0f);
		hpBars[hpBars.size()-1]->Pos().y -= hpBars.size() * 30.0f;
		break;

	case ProfessionType::FireMage:
		hpBars.push_back(new ProgressBar(L"Textures/UI/F_hpBar.png", L"Textures/UI/hp_bar_BG.png"));
		hpBars[hpBars.size() - 1]->SetParent(this);
		hpBars[hpBars.size() - 1]->Scale() = Vector3(0.5f, 1.55f, 1.0f);
		hpBars[hpBars.size() - 1]->Pos().y -= hpBars.size() * 30.0f;
		break;

	case ProfessionType::HolyPriest:
		hpBars.push_back(new ProgressBar(L"Textures/UI/H_hpBar.png", L"Textures/UI/hp_bar_BG.png"));
		hpBars[hpBars.size() - 1]->SetParent(this);
		hpBars[hpBars.size() - 1]->Scale() = Vector3(0.5f, 1.55f, 1.0f);
		hpBars[hpBars.size() - 1]->Pos().y -= hpBars.size() * 30.0f;
		break;

	case ProfessionType::MarksmanshipHunter:
		hpBars.push_back(new ProgressBar(L"Textures/UI/M_hpBar.png", L"Textures/UI/hp_bar_BG.png"));
		hpBars[hpBars.size() - 1]->SetParent(this);
		hpBars[hpBars.size() - 1]->Scale() = Vector3(0.5f, 1.55f, 1.0f);
		hpBars[hpBars.size() - 1]->Pos().y -= hpBars.size() * 30.0f;
		break;

	case ProfessionType::ProtectionWarrior:
		hpBars.push_back(new ProgressBar(L"Textures/UI/P_hpBar.png", L"Textures/UI/hp_bar_BG.png"));
		hpBars[hpBars.size() - 1]->SetParent(this);
		hpBars[hpBars.size() - 1]->Scale() = Vector3(0.5f, 1.55f, 1.0f);
		hpBars[hpBars.size() - 1]->Pos().y -= hpBars.size() * 30.0f;
		break;
	}
	
}

void PartyUI_Bar::SetHpPercent(float value, int index)
{
	if (index < 0 || index >= hpBars.size()) return;

	hpBars[index]->SetAmount(value);
}
