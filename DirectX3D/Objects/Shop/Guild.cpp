#include "Framework.h"
#include "Guild.h"

Guild::Guild()
{
	// 모델 설정
	{
		guild = new Model("Shop");
		trader = new Model("Trader");

		guild->SetParent(this);
		guild->GetMaterials()[0]->SetShader(L"Light/ItemLight.hlsl");
		guild->GetMaterials()[1]->SetShader(L"Light/ItemLight.hlsl");
		guild->Scale() *= 0.5f;

		trader->SetParent(this);
		trader->GetMaterials()[0]->SetShader(L"Light/ItemLight.hlsl");
	}

	// RS 설정 (guild 전용)
	{
		FOR(2) rs[i] = new RasterizerState();
		rs[1]->CullMode(D3D11_CULL_NONE);
	}

	// UI 설정
	{
		// Frame
		guildFrame = new Quad(L"Textures/UI/guildFrame.png");
		guildFrame->Scale() *= 1.2f;
		guildFrame->Pos() = { CENTER_X, CENTER_Y - 20.0f, 1.0f };

		// Icons
		icons.resize(5);

		for (int i = 0; i < 5; i++)
		{
			Quad* icon = new Quad(Vector2(140, 140));

			wstring temp = L"Textures/UI/Icons/" + to_wstring(i) + L".png";
			icon->GetMaterial()->SetDiffuseMap(temp);

			if (i <= 3)
			{
				icon->Pos() = Vector3(535 + (i * 130), 460, 0);
			}
			else if (i == 4)
			{
				icon->Pos() = Vector3(535, 280, 0);
			}
			
			icon->UpdateWorld();
			icons[i] = icon;
		}
	}
}

Guild::~Guild()
{
	SAFE_DEL(guild);
	SAFE_DEL(trader);
	SAFE_DEL(rs[1]);
	SAFE_DEL(rs[2]);
	SAFE_DEL(guildFrame);

}

void Guild::Update()
{
	guild->UpdateWorld();
	trader->UpdateWorld();

	// 플레이어가 10의 거리 이내로 접근하면 길드 UI 오픈
	if ((CH->GetPlayerData()->GlobalPos() - GlobalPos()).Length() < 10.0f && !Active())
	{
		SetActive(true);
		Audio::Get()->Play("OpenUI", 1.0f);
	}
	// 멀어지면 UI 비활성화
	else if ((CH->GetPlayerData()->GlobalPos() - GlobalPos()).Length() >= 10.0f)
	{
		SetActive(false);
	}

	if (!Active()) return;

	// 조작
	Control();

	guildFrame->UpdateWorld();
}

void Guild::Render()
{
	rs[1]->SetState();
	guild->Render();
	rs[0]->SetState();

	trader->Render();
}

void Guild::UIRender()
{
	if (!Active())
	{
		Vector3 screenPos = CAM->WorldToScreen(guild->GlobalPos());
		Font::Get()->RenderText("GUILD", { screenPos.x + 40.0f, screenPos.y + 150.0f });

		return;
	}
	guildFrame->Render();

	int idx = 0;
	for (Quad* icon : icons)
	{
		icon->Render();
		
		string temp1;
		string temp2;

		switch (idx)
		{
		case 0:
			temp1 = "  전사  ";
			temp2 = " [무기] ";
			break;
		case 1:
			temp1 = " 성기사 ";
			temp2 = " [보호] ";
			break;
		case 2:
			temp1 = " 마법사 ";
			temp2 = " [화염] ";
			break;
		case 3:
			temp1 = " 사냥꾼 ";
			temp2 = " [사격] ";
			break;
		case 4:
			temp1 = "  사제  ";
			temp2 = " [신성] ";
			break;
		}
	
		if (idx == 0 || idx == 4)
			Font::Get()->RenderText(temp1, { icon->Pos().x + 48, icon->Pos().y - 65.0f });
		else
			Font::Get()->RenderText(temp1, { icon->Pos().x + 45, icon->Pos().y - 65.0f });

		Font::Get()->RenderText(temp2, { icon->Pos().x + 45, icon->Pos().y - 85.0f });

		idx++;
	}
}

void Guild::GUIRender()
{
}

void Guild::Control()
{
	// 좌클릭 시
	if (KEY_DOWN(VK_LBUTTON))
	{
		int idx = 1;

		// 모든 아이콘을 순회하며 현재 클릭된 아이콘이 있는지 위치로 확인
		for (Quad* icon : icons)
		{
			if (mousePos.x <= icon->GlobalPos().x + icon->GetSize().x / 2 && mousePos.x >= icon->GlobalPos().x - icon->GetSize().x / 2 &&
				mousePos.y <= icon->GlobalPos().y + icon->GetSize().y / 2 && mousePos.y >= icon->GlobalPos().y - icon->GetSize().y / 2)
			{
				// 파티원의 수가 5인 이하라면 파티원 추가
				if (CH->GetCharcterData().size() < 6)
				{
					CH->NonPlayerSpawn(idx);
					Audio::Get()->Play("SelectNPC", 1.0f);
				}
					
			}
			idx++;
		}
		
	}
}
