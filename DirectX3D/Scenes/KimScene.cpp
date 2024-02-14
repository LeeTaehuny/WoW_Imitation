#include "Framework.h"
#include "KimScene.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Inventory/Slot.h"

//#include "Objects/Character_ver2/CH_Base_ver2.h"
//#include "Objects/Character_ver2/ProtectionWarrior_in.h"

#define UPDATE(k) if (k != nullptr) k->Update()
#define UPDATEWORLD(k) if (k != nullptr) k->UpdateWorld()
#define RENDER(k) if (k != nullptr) k->Render()
#define GUIRENDER(k) if (k != nullptr) k->GUIRender()

KimScene::KimScene()
{
	CH->PlayerSpawn(4);

	//CH->NonPlayerSpawn(1);
	//CH->NonPlayerSpawn(1);
	//CH->NonPlayerSpawn(1);

	MONSTER;
	ARROW;

	skill = new M_009_Volley();
	skill->SetOwner(CH->GetPlayerData());

	MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	MONSTER->SpawnScarecrow(Vector3(10));
	MONSTER->SpawnScarecrow(Vector3(-10));
	MONSTER->SpawnScarecrow(Vector3(-5));

	particle = new ParticleSystem("TextData/Particles/fire.fx");
}

KimScene::~KimScene()
{
	delete particle;
	
}

void KimScene::Update()
{
	//if (KEY_DOWN(VK_LEFT))
	//{
	//	MONSTER->SpawnSkeleton(Vector3());
	//}
	//if (KEY_DOWN(VK_RIGHT))
	//{
	//	MONSTER->SpawnSkeletonKnight(Vector3());
	//}
	
	if (KEY_DOWN('P'))
	{
		int gang = Random(1, 6);
		CH->NonPlayerSpawn(gang);
	}

	if (KEY_DOWN('1'))
	{
		particle->Play(Vector3());
	}

	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			// 마우스 위치의 Ray 생성
			Ray ray = CAM->ScreenPointToRay(mousePos);
			Contact contact;

			// 몬스터 배열 받기
			vector<MonsterBase*> monsters = MONSTER->GetScarecrow();

			// 몬스터 순회하며 Ray 충돌 연산
			for (MonsterBase* monster : monsters)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					// 충돌했다면 해당 몬스터를 내 타겟으로 설정
					targetMonster = monster;
				}
			}

			for (CH_Base_ver2* play : CH->GetCharcterData())
			{
				if (play->GetCollider()->IsRayCollision(ray, &contact))
				{
					targetNPC = play;
				}
			}
		}

		if (KEY_DOWN('K'))
		{
			if (ActiveSkill* c = dynamic_cast<ActiveSkill*>(skill))
			{
				if (UseType::character_Data == c->GetUsing())
				{
					c->UseSkill(targetNPC);
				}
				else if (UseType::collider_Data == c->GetUsing())
				{

				}
				else if (UseType::monster_Data == c->GetUsing())
				{
					c->UseSkill(targetMonster);
				}
				else if (UseType::NON_Data == c->GetUsing())
				{
					c->UseSkill();
				}
			}
		}
	}

	UPDATE(particle);
	CH->Update();
	skill->Update();
	MONSTER->Update();
	ARROW->Update();
}

void KimScene::PreRender()
{
	CH->PreRender();
}

void KimScene::Render()
{
	RENDER(particle);

	CH->Render();
	skill->Render();
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