#include "Framework.h"
#include "DungeonScene.h"
#include "Objects/Skills/SkillManager.h"
#include "Objects/UI/Button.h"

DungeonScene::DungeonScene()
{
	Audio::Get()->Add("Out_Dungeon", "Sounds/DungeonScene/icecrownraid_theforgeofsouls.ogg", true);
	Audio::Get()->Add("in_Dungeon", "Sounds/DungeonScene/ir_lightshammer1.mp3", true);
	Audio::Get()->Add("in_Dungeon2", "Sounds/DungeonScene/ir_walkj_01.mp3", true);

	Audio::Get()->Add("Open_Gate", "Sounds/DungeonScene/icecrown_door_02_main_open.ogg", true);
	Audio::Get()->Add("Open_Door", "Sounds/DungeonScene/icecrown_door_03_open.ogg", true);
	Audio::Get()->Add("IceWall_Break", "Sounds/DungeonScene/icecrown_cavein_close.ogg", true);
	Audio::Get()->Add("DungeonPotal", "Sounds/DungeonScene/fx_darkportal_open.ogg", false, false, false);

	{
		back_ = new Quad(L"Textures/UI/barbershop.png");
		//back_->Scale() *= 0.7f;
		back_->Pos() = Vector3(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f);
		back_->UpdateWorld();

		die_Gray = new Quad(L"Textures/UI/die_Scene.png");
		die_Gray->Pos() = Vector3(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f);
		die_Gray->Scale() *= 50;
		die_Gray->UpdateWorld();

		change_Scene = new Quad(Vector2(WIN_WIDTH, WIN_HEIGHT));
		change_Scene->GetMaterial()->SetDiffuseMap(L"Textures/SelectScene/loding.jpg");
		change_Scene->Pos() = Vector3(CENTER_X, CENTER_Y);
		change_Scene->SetActive(false);
		change_Scene->UpdateWorld();

		gaem_end = new Button(L"Textures/UI/button-up.png");
		gaem_end->Pos() = Vector3(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.4f);
		gaem_end->Scale() *= 2;
		gaem_end->SetDownEvent(bind(&DungeonScene::Game_End, this));
		gaem_end->Update();

		goTown = new Button(L"Textures/UI/button-up.png");
		goTown->Pos() = Vector3(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f);
		goTown->Scale() *= 2;
		goTown->SetDownEvent(bind(&DungeonScene::Change_Town, this));
	}
}

DungeonScene::~DungeonScene()
{
	delete dungeon;

	delete back_;
	delete die_Gray;
	delete gaem_end;
	delete goTown;
}

void DungeonScene::Start()
{
	dungeon = new Dungeon();

	float Time = 7.0f;

	Audio::Get()->Play("Out_Dungeon", 0.7f);

	// 플레이어 위치 조정
	CH->GetPlayerData()->Pos() = dungeon->GetSpawnPoint_P();
	CH->GetPlayerData()->SetHeight(0.0f);
	CH->GetPlayerData()->Rot().y = 3.15f;
	CH->GetPlayerData()->Update();

	for (int i = 1; i < CH->GetCharcterData().size(); i++)
	{
		CH->GetCharcterData()[i]->Pos() = CH->GetPlayerData()->Pos();
		CH->GetCharcterData()[i]->SetHeight(0.0f);
		CH->GetCharcterData()[i]->Rot().y = 3.15f;
	}

	Mounga_die = false;
	pop_time = Max_pop_time;

	// 초기화
	isOpenGate = false;
	isOpenDoor = false;
	in_A = false;
	in_B = false;
	ClearDungeon = false;
}

void DungeonScene::Update()
{
	if (Mounga_die)
	{
		Scene_Chnage();
		return;
	}

	dungeon->Update();
	CH->Update();
	MONSTER->Update();
	SKILL->Update();

	if (CH->GetPlayerData()->GetStat().hp <= 0)
	{
		goTown->Update();
		gaem_end->Update();

		if (!sound_change)
		{
			sound_change = true;
			
		}
	}

	for (int i = 0; i < CH->GetCharcterData().size(); i++)
	{
		if (dungeon->IsCollision(CH->GetCharcterData()[i]->GetCollider()))
		{
			CH->GetCharcterData()[i]->SetHeight(0.0f);
		}
	}

	// 플레이어가 포탈에 닿은경우
	if (dungeon->PotalCollision(CH->GetPlayerData()->GetCollider())) 
	{
		Environment::Get()->GetLight(0)->color = { 1.0f, 1.0f, 1.0f, 1 };
		Audio::Get()->Stop("Out_Dungeon");
		Audio::Get()->Stop("IceWall_Break");
		Audio::Get()->Play("DungeonPotal", 0.7f);
		SceneManager::Get()->ChangeScene("Boss");
	}

	// 1번방 문 열리기
	if (dungeon->IsOpenGateCollider(CH->GetPlayerData()->GetCollider()) 
		&& isOpenGate == false)
	{
		dungeon->OpenDoor(true);
		Audio::Get()->Play("Open_Gate", 0.7f);
		Audio::Get()->Stop("Out_Dungeon");
		Audio::Get()->Play("in_Dungeon", 0.7f);;

		isOpenGate = true;
	}

	// 1번방 문이 열렸고, 중앙 충돌체와 충돌하면 몬스터 스폰
	if (isOpenGate == true &&
		dungeon->IsinDungeon(CH->GetPlayerData()->GetCollider()) && 
		in_A == false)
	{
		for (int i = 0; i < dungeon->SpawnMonsters_A().size(); i++)
		{
			  MONSTER->SpawnSkeleton(dungeon->SpawnMonsters_A()[i]);
			  MONSTER->GetSkeleton()[MONSTER->GetSkeleton().size() - 1]->GetTransform()->Rot().y = 1.575f;
		}
		//isOpenGate = false;
		in_A = true;
	}

	// 1번방 몬스터가 스폰되었으며, 모두 죽었다면 2번방 문 열리기
	if (in_A == true &&
		MONSTER->GetSkeleton().size() == 0 &&
		isOpenDoor == false)
	{
		dungeon->OpenDoor_I(true);
		Audio::Get()->Play("Open_Door", 0.7f);
		Audio::Get()->Pause("in_Dungeon");
		Audio::Get()->Play("in_Dungeon2", 0.7f);

		isOpenDoor = true;
	}

	// 2번방 문이 열렸고, 중앙 충돌체와 충돌하면 몬스터 스폰
	if (isOpenDoor == true &&
		dungeon->IsinDungeon2(CH->GetPlayerData()->GetCollider()) && 
		in_B == false)
	{
		for (int i = 0; i < dungeon->SpawnMonsters_B().size(); i++)
		{
			  MONSTER->SpawnSkeletonKnight(dungeon->SpawnMonsters_B()[i]);
			  MONSTER->GetSkeleton_Knight()[MONSTER->GetSkeleton_Knight().size() - 1]->GetTransform()->Rot().y = 1.575f;
		}
		in_B = true;
	}

	// 2번방 몬스터가 스폰되었으며, 모두 죽었다면 포탈 벽 부시기
	if (in_B == true && 
		MONSTER->GetSkeleton_Knight().size() == 0 &&
		ClearDungeon == false)
	{
		dungeon->IsClear(true);
		Audio::Get()->Play("IceWall_Break", 1.0f);
		Audio::Get()->Play("Out_Dungeon", 0.7f);

		ClearDungeon = true;
	}
}

void DungeonScene::PreRender()
{
}

void DungeonScene::Render()
{
	dungeon->Render();
	CH->Render();

	MONSTER->Render();
}

void DungeonScene::PostRender()
{
	if (CH->GetPlayerData()->GetStat().hp <= 0)
	{
		pop_time -= DELTA;
		if (pop_time >= 0)
		{
			return;
		}

		if (CH->GetPlayerData()->GetStat().hp <= 0 && !Mounga_die)
		{
			die_Gray->Render();
			back_->Render();
			gaem_end->Render();
			goTown->Render();

			string rito = "당신은 죽었습니다.";
			Font::Get()->RenderText(rito, { 735, 450 });
			rito = "다시 도전하시겠습니까?";
			Font::Get()->RenderText(rito, { 750, 420 });

			rito = "다시 도전";
			Font::Get()->RenderText(rito, { 687, 363 });

			rito = "게임 종료";
			Font::Get()->RenderText(rito, { 687, 291 });
		}
	}

	SKILL->PostRender();
	CH->PostRender();

	MONSTER->PostRender();
}

void DungeonScene::GUIRender()
{
}

void DungeonScene::Change_Town()
{
	Mounga_die = true;
	change_Scene->SetActive(true);
}

void DungeonScene::Game_End()
{
	PostQuitMessage(0);
}

void DungeonScene::Scene_Chnage()
{
	vector<CH_Base_ver2*> Position_Select = CH->GetCharcterData();
	for (int i = 0; i < Position_Select.size(); i++)
	{
		Position_Select[i]->GetStat().hp = Position_Select[i]->GetStat().maxHp;
		Position_Select[i]->SetActive(true);

		switch (Position_Select[i]->GetProfessionType())
		{
		case ProfessionType::ArmsWarrior:
			if (ArmsWarrior_in* c = dynamic_cast<ArmsWarrior_in*>(Position_Select[i]))
			{
				c->SetState(ArmsWarrior_in::State::IDLE1);
			}
			break;

		case ProfessionType::FireMage:
			if (FireMage_in* c = dynamic_cast<FireMage_in*>(Position_Select[i]))
			{
				c->SetState(FireMage_in::State::IDLE1);
			}
			break;

		case ProfessionType::HolyPriest:
			if (HolyPriest_in* c = dynamic_cast<HolyPriest_in*>(Position_Select[i]))
			{
				c->SetState(HolyPriest_in::State::IDLE1);
			}
			break;

		case ProfessionType::MarksmanshipHunter:
			if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(Position_Select[i]))
			{
				c->SetState(MarksmanshipHunter_in::State::IDLE1);
			}
			break;

		case ProfessionType::ProtectionWarrior:
			if (ProtectionWarrior_in* c = dynamic_cast<ProtectionWarrior_in*>(Position_Select[i]))
			{
				c->SetState(ProtectionWarrior_in::State::IDLE1);
			}
			break;
		}
	}

	Audio::Get()->Stop("Out_Dungeon");
	Audio::Get()->Stop("IceWall_Break");
	Audio::Get()->Stop("in_Dungeon");
	Audio::Get()->Stop("in_Dungeon2");

	Environment::Get()->GetLight(0)->color = { 1.0f, 1.0f, 1.0f, 1 };

	vector<MonsterBase*> mon1 = MONSTER->GetSkeleton();
	for (int i = 0; i < mon1.size(); i++)
	{
		mon1[i]->GetTransform()->SetActive(false);
		mon1[i]->GetCollider()->SetActive(false);
	}
	mon1 = MONSTER->GetSkeleton_Knight();
	for (int i = 0; i < mon1.size(); i++)
	{
		mon1[i]->GetTransform()->SetActive(false);
		mon1[i]->GetCollider()->SetActive(false);
	}

	SceneManager::Get()->ChangeScene("Town");
}