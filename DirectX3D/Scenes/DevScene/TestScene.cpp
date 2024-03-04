#include "Framework.h"
#include "TestScene.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Skills/SkillManager.h"
#include "Objects/UI/PlayerUI_Bar.h"
#include "Objects/UI/MonsterUI_Bar.h"
#include "Objects/UI/PartyUI_Bar.h"


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
	//p = new PartyUI_Bar();
	shop = new Shop();
	//CH->PlayerSpawn(3);
	//MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	//MONSTER->SpawnScarecrow(Vector3(0, 0, 4));
	//MONSTER->SpawnScarecrow(Vector3(0, 0, 3));
	//MONSTER->SpawnScarecrow(Vector3(0, 0, 2));
	//MONSTER->SpawnSkeleton(Vector3(10));
	//MONSTER->SpawnSkeletonKnight(Vector3(20));


	//for (int i = 1; i < CH->GetCharcterData().size(); i++)
	//{
	//	p->AddPlayer(i);
	//}

	//p->Pos() = { CENTER_X + 480.0f, CENTER_Y , 0 };
	//CH->NonPlayerSpawn(3);
	//CH->NonPlayerSpawn(5);
	//CH->NonPlayerSpawn(4);
	

	

	//MONSTER->SetTarget(CH->GetPlayerData());

	//SKILL->Init(CH->GetPlayerData());

	//CAM->SetTarget(CH->GetPlayerData());

	
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	//SKILL->Update();
	shop->Update();

	//MONSTER->Update();

	CH->Update();

	if (KEY_DOWN('P'))
	{
		int temp = Random(1, 5);
		CH->NonPlayerSpawn(temp);
	}
	
	if (KEY_DOWN('L'))
	{
		// 마우스 위치의 Ray 생성
		Ray ray = CAM->ScreenPointToRay(mousePos);
		Contact contact;
	
		vector<CH_Base_ver2*> player = CH->GetCharcterData();
	
		for (CH_Base_ver2* p : player)
		{
	
			if (p->GetCollider()->IsRayCollision(ray, &contact))
			{
				p->OnHit(100);
				break;
			}
		}
	}

	//hpBar->UpdateWorld();
	//mpBar->UpdateWorld();
	//HpFrame->UpdateWorld();

}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	//MONSTER->Render();
	
	CH->Render();
}

void TestScene::PostRender()
{
	//SKILL->PostRender();
	shop->UIRender();
	CH->PostRender();
	//MONSTER->PostRender();


	//UI 추가
	//hpBar->Render();
	//mpBar->Render();
	//HpFrame->Render();
}

void TestScene::GUIRender()
{
	CH->GUIRender();
}

void TestScene::Start()
{
}

void TestScene::End()
{
}
