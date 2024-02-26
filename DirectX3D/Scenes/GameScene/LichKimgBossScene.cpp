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

	reTry = new Button(L"Textures/UI/button-up.png");
	reTry->Pos() = Vector3(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.4f);
	reTry->Scale() *= 2;
	reTry->SetDownEvent(bind(&LichKimgBossScene::PL_Die_Change_Town, this));
	reTry->Update();
	
	goTown= new Button(L"Textures/UI/button-up.png");
	goTown->Pos() = Vector3(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.4f);
	goTown->Scale() *= 2;
	goTown->SetDownEvent(bind(&LichKimgBossScene::BO_Die_Change_Town, this));
}

LichKimgBossScene::~LichKimgBossScene()
{
	delete map;
	delete back_;
	delete die_Gray;
	delete reTry;
	delete goTown;
	delete change_Scene;
}

void LichKimgBossScene::Start()
{
	CH->PlayerSpawn(4);
	//CH->GetPlayerData()->EquipWeapon(new Weapon("hammer_1", WeaponType::Hammer));
	CH->GetPlayerData()->EquipWeapon(new Weapon("bow_1", WeaponType::Bow));
	SKILL->Init(CH->GetPlayerData());
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

	
	MONSTER->SpawnLickKing(Vector3());
	bossData = MONSTER->GetLichKing();
	if (Boss_LichKing* c = dynamic_cast<Boss_LichKing*>(MONSTER->GetLichKing()))
	{
		c->SetBossMap(map);
	}
}
void LichKimgBossScene::End()
{
	delete MONSTER->GetLichKing();
	bossData = nullptr;
}

void LichKimgBossScene::Update()
{
	if (pl_die || bo_die) 
	{
		Scene_Chnage();
		return;
	}
	map->Update();

	if (playerData->GetStat().hp <= 0)
	{
		reTry->Update();
	}
	if (bossData->GetHpPercent() <= 0)
	{
		goTown->Update();
	}

	SKILL->Update();
	CH->Update();
	MONSTER->Update();
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
	if (playerData->GetStat().hp <= 0 && !bo_die && !pl_die)
	{
		die_Gray->Render();
		back_->Render();
		reTry->Render();

		string rito = "당신은 죽었습니다.";
		Font::Get()->RenderText(rito, { 735, 450 });
		rito = "다시 도전하시겠습니까?";
		Font::Get()->RenderText(rito, { 750, 420 });

		rito = "다시 도전";
		Font::Get()->RenderText(rito, { 691, 291 });
	}

	if (bossData->GetHpPercent() <= 0 && !bo_die)
	{
		back_->Render();
		goTown->Render();

		string rito = "리치왕을 쓰러트렸습니다.";
		Font::Get()->RenderText(rito, { 763, 450 });
		rito = "마을로 돌아가시겠습니까?";
		Font::Get()->RenderText(rito, { 762, 400 });

		rito = "마을로 귀환";
		Font::Get()->RenderText(rito, { 693, 291 });
	}
	
	if (pl_die || bo_die)
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
}

void LichKimgBossScene::PL_Die_Change_Town()
{
	pl_die = true;
	change_Scene->SetActive(true);
}

void LichKimgBossScene::BO_Die_Change_Town()
{
	bo_die = true;
	change_Scene->SetActive(true);
}

void LichKimgBossScene::Scene_Chnage()
{
	// 나중에 마을 씬으로 변경해줄 필요 있음
	SceneManager::Get()->ChangeScene("KIM");
}