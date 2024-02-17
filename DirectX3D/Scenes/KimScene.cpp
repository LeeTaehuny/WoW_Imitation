#include "Framework.h"
#include "KimScene.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Inventory/Slot.h"

#include "Objects/Skills/FireMage_Skill/F_005_PhoenixFlame.h"
#include "Objects/Skills/FireMage_Skill/F_009_Combustion.h"
#include "Objects/Skills/FireMage_Skill/F_010_Meteor.h"

//#include "Objects/Character_ver2/CH_Base_ver2.h"
//#include "Objects/Character_ver2/ProtectionWarrior_in.h"

#define UPDATE(k) if (k != nullptr) k->Update()
#define UPDATEWORLD(k) if (k != nullptr) k->UpdateWorld()
#define RENDER(k) if (k != nullptr) k->Render()
#define GUIRENDER(k) if (k != nullptr) k->GUIRender()

KimScene::KimScene()
{
	CH->PlayerSpawn(3);

	CH->NonPlayerSpawn(3);
	//CH->NonPlayerSpawn(2);
	//CH->NonPlayerSpawn(1);
	//CH->NonPlayerSpawn(1);

	MONSTER;
	ARROW;

	skills = new F_005_PhoenixFlame();
	skills->SetOwner(CH->GetPlayerData());

	//MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	//MONSTER->SpawnScarecrow(Vector3(10));
	//MONSTER->SpawnScarecrow(Vector3(-10));
	//MONSTER->SpawnScarecrow(Vector3(-5));

	//MONSTER->SpawnSkeleton(Vector3(10));	
	//MONSTER->SpawnSkeletonKnight(Vector3(10));

	//particle = new ParticleSystem("TextData/Particles/Fire/fireBall.fx");
}

KimScene::~KimScene()
{
	delete particle;
	delete skills;
}

void KimScene::Update()
{
	if (KEY_DOWN(VK_LEFT))
	{
		MONSTER->SpawnSkeleton(Vector3());
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		MONSTER->SpawnSkeletonKnight(Vector3());
	}
	if (KEY_DOWN(VK_DOWN))
	{
		MONSTER->SpawnScarecrow(Vector3());
	}
	
	if (KEY_DOWN('P'))
	{
		int gang = Random(1, 6);
		CH->NonPlayerSpawn(4);
	}

	if (KEY_DOWN(VK_NUMPAD5))
	{
		CH->GetPlayerData()->GetStat().hp -= 100;;
	}
	if (KEY_DOWN(VK_NUMPAD6))
	{
		CH->GetCharcterData()[1]->GetStat().hp -= 100;
	}

	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			{
				Ray ray = CAM->ScreenPointToRay(mousePos);
				Contact contact;

				// 몬스터 배열 받기
				vector<MonsterBase*> monsters = MONSTER->GetScarecrow();
				for (MonsterBase* monster : monsters)
				{
					if (monster->GetCollider()->IsRayCollision(ray, &contact) &&
						monster->GetCollider()->Active())
					{
						// 충돌했다면 해당 몬스터를 내 타겟으로 설정
						targetMonster = monster;
						break;
					}
				}
				monsters = MONSTER->GetSkeleton();
				for (MonsterBase* monster : monsters)
				{
					if (monster->GetCollider()->IsRayCollision(ray, &contact) &&
						monster->GetCollider()->Active())
					{
						// 충돌했다면 해당 몬스터를 내 타겟으로 설정
						targetMonster = monster;
						break;
					}
				}
				monsters = MONSTER->GetSkeleton_Knight();
				for (MonsterBase* monster : monsters)
				{
					if (monster->GetCollider()->IsRayCollision(ray, &contact) &&
						monster->GetCollider()->Active())
					{
						// 충돌했다면 해당 몬스터를 내 타겟으로 설정
						targetMonster = monster;
						break;
					}
				}

				if (targetMonster)
				{
					CH->GetPlayerData()->SetSelectTarget(targetMonster);
					CH->GetPlayerData()->SetAttackSignal(0);
				}

				for (CH_Base_ver2* play : CH->GetCharcterData())
				{
					if (play->GetCollider()->IsRayCollision(ray, &contact))
					{
						targetNPC = play;
						break;
					}
				}
			}
		}
	}

	if (KEY_DOWN('K'))
	{
		skills->UseSkill(targetMonster);
	}

	skills->Update();
	CH->Update();
	MONSTER->Update();
	ARROW->Update();
}

void KimScene::PreRender()
{
	CH->PreRender();
}

void KimScene::Render()
{
	skills->Render();
	CH->Render();
	MONSTER->Render();
	ARROW->Render();
}

void KimScene::PostRender()
{
	CH->PostRender();
}

void KimScene::GUIRender()
{
	CH->GUIRender();
}