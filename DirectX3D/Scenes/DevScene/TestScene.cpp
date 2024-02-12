#include "Framework.h"
#include "TestScene.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Skills/FireMage_Skill/F_001_Pyroblast.h"
#include "Objects/Skills/FireMage_Skill/F_002_FireBlast.h"
#include "Objects/Skills/FireMage_Skill/F_003_Pyrotechnics.h"
#include "Objects/Skills/FireMage_Skill/F_004_Scorch.h"
#include "Objects/Skills/FireMage_Skill/F_005_PhoenixFlame.h"
#include "Objects/Skills/FireMage_Skill/F_006_SurgingBlaze.h"
#include "Objects/Skills/FireMage_Skill/F_007_SearingTouch.h"
#include "Objects/Skills/FireMage_Skill/F_008_FlameOn.h"
#include "Objects/Skills/FireMage_Skill/F_009_Combustion.h"
#include "Objects/Skills/FireMage_Skill/F_010_Meteor.h"

TestScene::TestScene()
{
	//paladin = new ModelAnimatorInstancing("FireMage");
	//paladin->ReadClip("Idle_1");
	//paladin->ReadClip("Idle_2");
	//paladin->ReadClip("Attack_1");
	//paladin->ReadClip("Attack_2");
	//paladin->ReadClip("Attack_3");
	//paladin->ReadClip("Walk_F");
	//paladin->ReadClip("Walk_B");
	//paladin->ReadClip("Walk_L");
	//paladin->ReadClip("Walk_R");
	//paladin->ReadClip("Die_1");
	//paladin->ReadClip("Hit_1");
	//paladin->ReadClip("Jump");

	//Transform* transform = paladin->Add();
	//player = new FireMage_in(CreatureType::Player, transform, paladin, count++);
	//CAM->SetTarget(player);
	
	//shop = new Shop();


	MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	MONSTER->SpawnScarecrow(Vector3(0, 0, 4));
	MONSTER->SpawnScarecrow(Vector3(-10));

	//skill1 = new F_001_Pyroblast();
	//skill2 = new F_002_FireBlast();
	//skill3 = new F_003_Pyrotechnics();
	//skill4 = new F_004_Scorch();
	//skill5 = new F_005_PhoenixFlame();
	//skill6 = new F_006_SurgingBlaze();
	//skill7 = new F_007_SearingTouch();
	//skill8 = new F_008_FlameOn();
	//skill9 = new F_009_Combustion();
	//skill10 = new F_010_Meteor();
	//
	//skill1->SetOwner(player);
	//skill2->SetOwner(player);
	//skill3->SetOwner(player);
	//skill4->SetOwner(player);
	//skill5->SetOwner(player);
	//skill6->SetOwner(player);
	//skill7->SetOwner(player);
	//skill8->SetOwner(player);
	//skill9->SetOwner(player);
	//skill10->SetOwner(player);
	//
	//player->GetSkillList().push_back(skill1);
	//player->GetSkillList().push_back(skill2);
	//player->GetSkillList().push_back(skill3);
	//player->GetSkillList().push_back(skill4);
	//player->GetSkillList().push_back(skill5);
	//player->GetSkillList().push_back(skill6);
	//player->GetSkillList().push_back(skill7);
	//player->GetSkillList().push_back(skill8);
	//player->GetSkillList().push_back(skill9);
	//player->GetSkillList().push_back(skill10);

	CH->PlayerSpawn(2);

	MONSTER->SetTarget(CH->GetPlayerData()->GetCollider());

	weapon = new Weapon("sword_1", WeaponType::Sword);

	if (Weapon* w = dynamic_cast<Weapon*>(weapon))
	{
		CH->GetPlayerData()->EquipWeapon(w);
		//player->EquipWeapon(w);
		w->SetOwner(CH->GetPlayerData());
	}
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	//shop->Update();
	//
	//// 상점 - 플레이어 상호작용
	//{
	//	if ((player->GlobalPos() - shop->GlobalPos()).Length() < 10.0f)
	//	{
	//		shop->SetActive(true);
	//	}
	//	else
	//	{
	//		shop->SetActive(false);
	//	}
	//
	//	if (shop->Active())
	//	{
	//		const vector<Slot*> slots = shop->GetItemSlots();
	//		const vector<Slot*> items = player->GetInventory()->GetInvSlots();
	//
	//		int idx = 0;
	//		for (Slot* slot : slots)
	//		{
	//			if (mousePos.x <= slot->GlobalPos().x + slot->GetSize().x && mousePos.x >= slot->GlobalPos().x - slot->GetSize().x &&
	//				mousePos.y <= slot->GlobalPos().y + slot->GetSize().y && mousePos.y >= slot->GlobalPos().y - slot->GetSize().y)
	//			{
	//				if (KEY_DOWN(VK_RBUTTON))
	//				{
	//					string tmpName = shop->GetItemName(idx);
	//
	//					if (tmpName.size())
	//					{
	//						shop->PurchaseItem(tmpName, player->GetInventory());
	//					}
	//				}
	//			}
	//
	//			idx++;
	//		}
	//
	//		idx = 0;
	//		for (Slot* item : items)
	//		{
	//			if (mousePos.x <= item->GlobalPos().x + 33.0f && mousePos.x >= item->GlobalPos().x - 33.0f &&
	//				mousePos.y <= item->GlobalPos().y + 33.0f && mousePos.y >= item->GlobalPos().y - 33.0f)
	//			{
	//				if (KEY_DOWN(VK_RBUTTON))
	//				{
	//					shop->SellItem(idx, player->GetInventory());
	//				}
	//			}
	//
	//			idx++;
	//		}
	//	}
	//}
	//
	//// 임시 스킬 사용 테스트 (좌클릭 타겟 설정, K : 스킬 사용)
	//{
	//	if (KEY_DOWN(VK_LBUTTON))
	//	{
	//		// 마우스 위치의 Ray 생성
	//		Ray ray = CAM->ScreenPointToRay(mousePos);
	//		Contact contact;
	//
	//		// 몬스터 배열 받기
	//		vector<MonsterBase*> monsters = MONSTER->GetScarecrow();
	//
	//		// 몬스터 순회하며 Ray 충돌 연산
	//		for (MonsterBase* monster : monsters)
	//		{
	//			if (monster->GetCollider()->IsRayCollision(ray, &contact))
	//			{
	//				// 충돌했다면 해당 몬스터를 내 타겟으로 설정
	//				targetMonster = monster;
	//			}
	//		}
	//	}
	//
	//	if (KEY_DOWN(VK_F1))
	//	{
	//		if (targetMonster != nullptr)
	//			skill1->UseSkill(targetMonster->GetCollider());
	//	}
	//
	//	if (KEY_DOWN(VK_F2))
	//	{
	//		if (targetMonster != nullptr)
	//			skill2->UseSkill(targetMonster->GetCollider());
	//	}
	//
	//	if (KEY_DOWN(VK_F3))
	//	{
	//		skill3->UseSkill();
	//	}
	//
	//	if (KEY_DOWN(VK_F4))
	//	{
	//		if (targetMonster != nullptr)
	//			skill4->UseSkill(targetMonster->GetCollider());
	//	}
	//
	//	if (KEY_DOWN(VK_F5))
	//	{
	//		if (targetMonster != nullptr)
	//			skill5->UseSkill(targetMonster->GetCollider());
	//	}
	//
	//	if (KEY_DOWN(VK_F6))
	//	{
	//		skill6->UseSkill();
	//	}
	//
	//	if (KEY_DOWN(VK_F7))
	//	{
	//		skill7->UseSkill();
	//	}
	//
	//	if (KEY_DOWN(VK_F8))
	//	{
	//		skill8->UseSkill();
	//	}
	//
	//	if (KEY_DOWN(VK_F9))
	//	{
	//		skill9->UseSkill();
	//	}
	//
	//	if (KEY_DOWN(VK_F10))
	//	{
	//		if (targetMonster != nullptr)
	//			skill10->UseSkill(targetMonster->GetCollider());
	//	}
	//}
	//
	//paladin->Update();
	//player->Update();
	MONSTER->Update();
	//skill1->Update();
	//skill2->Update();
	//skill4->Update();
	//skill5->Update();
	//skill9->Update();
	//skill10->Update();

	CH->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	//paladin->Render();
	//player->Render();
	MONSTER->Render();
	//skill1->Render();
	//skill2->Render();
	//skill4->Render();
	//skill5->Render();
	//skill9->Render();
	//skill10->Render();
	CH->Render();
}

void TestScene::PostRender()
{
	//player->UIRender();
	//shop->UIRender();
}

void TestScene::GUIRender()
{
	//weapon->GUIRender();
	//potion->GUIRender();
}

void TestScene::Start()
{
}

void TestScene::End()
{
}
