#include "Framework.h"
#include "LichKimgBossScene.h"

#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Skills/SkillManager.h"

LichKimgBossScene::LichKimgBossScene()
{
	map = new BossMap();

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
	gaem_end->SetDownEvent(bind(&LichKimgBossScene::Game_End, this));
	gaem_end->Update();
	
	goTown= new Button(L"Textures/UI/button-up.png");
	goTown->Pos() = Vector3(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f);
	goTown->Scale() *= 2;
	goTown->SetDownEvent(bind(&LichKimgBossScene::Change_Town, this));

	Audio::Get()->Add("bossScene_main_bgm", "Sounds/BossScene/BGM/main.mp3", true);
	Audio::Get()->Add("bossScene_end", "Sounds/BossScene/BGM/end.mp3", true);
}

LichKimgBossScene::~LichKimgBossScene()
{
	delete map;
	delete back_;
	delete die_Gray;
	delete gaem_end;
	delete goTown;
	delete change_Scene;
}

void LichKimgBossScene::Start()
{
	//CH->PlayerSpawn(2);
	//SKILL->Init(CH->GetPlayerData());

	sound_change = false;
	Audio::Get()->Play("bossScene_main_bgm");

	playerData = CH->GetPlayerData();

	vector<CH_Base_ver2*> Position_Select = CH->GetCharcterData();
	float xxxx = -40;
	float zzzz = 0;
	float zzzz22 = 0;
	int charcter_count = 0;
	float nanum = 1;
	float nujec = 0.5f;
	Vector3 position_active;
	for (int i = 0; i < Position_Select.size(); i++)
	{
		position_active = Vector3(xxxx, 0, zzzz);
		Position_Select[i]->Pos() = position_active;
		Position_Select[i]->SetHeight(0);
		Position_Select[i]->Pos().y = 0;
		Position_Select[i]->Rot().y = 0;
		Position_Select[i]->Rot().y -= XM_PI * 0.5f;
		Position_Select[i]->Update();

		if (1 - nanum == 0)
		{
			charcter_count++;
			nanum = 0;
			xxxx += -5;
			zzzz22 += 5;
		}
		else
		{
			if (nanum == 0)
			{
				zzzz = -zzzz22;
			}
			else
			{
				zzzz = zzzz22;
			}
			nanum += nujec;
		}
	}

	map->SetPhase(0);
	if (!MONSTER->GetLichKing())
	{
		MONSTER->SpawnLickKing(Vector3());
		bossData = MONSTER->GetLichKing();
		if (Boss_LichKing* c = dynamic_cast<Boss_LichKing*>(MONSTER->GetLichKing()))
		{
			c->SetBossMap(map);
		}
	}

	if (Boss_LichKing* c = dynamic_cast<Boss_LichKing*>(MONSTER->GetLichKing()))
	{
		c->Spawn(Vector3());
	}
	
	Mounga_die = false;
	pop_time = Max_pop_time;

	pop_time = Max_pop_time;
}

void LichKimgBossScene::Update()
{
	if (Mounga_die)
	{
		Scene_Chnage();
		return;
	}
	map->Update();

	if (playerData->GetStat().hp <= 0 || bossData->GetHpPercent() <= 0)
	{
		goTown->Update();
		gaem_end->Update();

		if (!sound_change)
		{
			sound_change = true;
			Audio::Get()->Stop("bossScene_main_bgm");
			Audio::Get()->Play("bossScene_end");
		}
	}
	

	SKILL->Update();
	vector<CH_Base_ver2*> con = CH->GetCharcterData();
	//for (int i = 0; i < con.size(); i++)
	//{
	//	float vaul = 0.9f;
	//	Vector3 ratio = map->Getgound01()->Scale() * vaul;
	//	switch (map->GetPhase())
	//	{
	//	case 1:
	//		ratio = map->Getgound02()->Scale() * vaul;
	//		break;
	//	
	//	case 3:
	//		ratio = map->Getgound02()->Scale() * vaul;
	//		break;
	//	}
	//
	//	if (con[i]->Pos().x >= ratio.x || con[i]->Pos().x <= -ratio.x ||
	//		con[i]->Pos().z >= ratio.z || con[i]->Pos().z <= -ratio.z)
	//	{
	//		con[i]->SetHeight(-100);
	//	}
	//
	//	if (con[i]->Pos().y <= -50)
	//	{
	//		con[i]->OnHit(99999);
	//	}
	//}

	CH->Update();
	MONSTER->Update();

	for (int i = 0; i < CH->GetCharcterData().size(); i++)
	{
		if (map->IsCollision(CH->GetCharcterData()[i]->GetCollider()));

		if (!map->IsCollision(CH->GetCharcterData()[i]->GetCollider()))
		{
			con[i]->SetHeight(-150);
		}

		if (con[i]->Pos().y <= -50)
		{
			con[i]->OnHit(99999);
		}
	}
}

void LichKimgBossScene::PreRender()
{
	CH->PreRender();
}

void LichKimgBossScene::Render()
{
	map->Render();

	CH->Render();
	MONSTER->Render();
}

void LichKimgBossScene::PostRender()
{
	if (playerData->GetStat().hp <= 0 || bossData->GetHpPercent() <= 0)
	{
		pop_time -= DELTA;
		if (pop_time >= 0)
		{
			return;
		}

		if (playerData->GetStat().hp <= 0 && !Mounga_die)
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

		if (bossData->GetHpPercent() <= 0 && !Mounga_die)
		{
			back_->Render();
			gaem_end->Render();

			string rito = "리치왕을 쓰러트렸습니다.";
			Font::Get()->RenderText(rito, { 763, 450 });
			rito = "게임을 종료하시겠습니까?";
			Font::Get()->RenderText(rito, { 766, 400 });

			rito = "게임 종료";
			Font::Get()->RenderText(rito, { 687, 291 });
		}
	}	
	
	if (Mounga_die)
	{
		change_Scene->Render();
		return;
	}

	SKILL->PostRender();
	CH->PostRender();
	MONSTER->PostRender();
}

void LichKimgBossScene::GUIRender()
{
	CH->GUIRender();

	MONSTER->GUIRender();
}

void LichKimgBossScene::Change_Town()
{
	Mounga_die = true;
	change_Scene->SetActive(true);
}

void LichKimgBossScene::Game_End()
{
	PostQuitMessage(0);
}

void LichKimgBossScene::Scene_Chnage()
{
	vector<CH_Base_ver2*> Position_Select = CH->GetCharcterData();
	for (int i = 0; i < Position_Select.size(); i++)
	{
		Position_Select[i]->GetStat().hp = Position_Select[i]->GetStat().maxHp;
		Position_Select[i]->SetActive(true);
	}

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
	mon1 = MONSTER->GetIceBall();
	for (int i = 0; i < mon1.size(); i++)
	{
		mon1[i]->GetTransform()->SetActive(false);
		mon1[i]->GetCollider()->SetActive(false);
	}
	mon1 = MONSTER->GetVAlkier();
	for (int i = 0; i < mon1.size(); i++)
	{
		mon1[i]->GetTransform()->SetActive(false);
		mon1[i]->GetCollider()->SetActive(false);
	}

	bossData->GetTransform()->SetActive(false);
	bossData->GetCollider()->SetActive(false);

	Audio::Get()->Stop("bossScene_main_bgm");
	Audio::Get()->Stop("bossScene_end");

	SceneManager::Get()->ChangeScene("Town");
}