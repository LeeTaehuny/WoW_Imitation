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
	instacning01(); // 팔라딘
	//instacning02(); // 화염 법사
	//instacning03(); // 사제
	//instacning04(); // 무기 전사
	//instacning05(); // 사냥꾼

	Transform* transform = paladin->Add();
	player = new ProtectionWarrior_in(CreatureType::Player, transform, paladin, count);
	//CAM->SetTarget(player);
	count++;
	//MONSTER->SetTarget(mainholypriestadinayer->GetCollider());

	skill = new P_004_HOTR();
	skill->SetOwner(player);

	//spawn(holypriest);
	//spawn(firemage);
	//spawn(firemage);
	//spawn(holypriest);
	//spawn(armswarrior);
	//spawn(armswarrior);
	//spawn(marksmanshiphunter);
	//spawn(marksmanshiphunter);
	//spawn(holypriest);
	MONSTER;

	MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	MONSTER->SpawnScarecrow(Vector3(10));
	MONSTER->SpawnScarecrow(Vector3(-10));
	MONSTER->SpawnScarecrow(Vector3(-5));

	particle = new ParticleSystem("TextData/Particles/fire.fx");
}

KimScene::~KimScene()
{
	//delete mainholypriestadinayer;
	delete paladin;
	delete firemage;
	delete holypriest;
	delete armswarrior;
	delete marksmanshiphunter;
	delete particle;

	delete player;

	for (CH_Base_ver2* ch : NPC)
		delete ch;
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

	//if (KEY_DOWN('P'))
	//{
	//	spawn();
	//}

	UPDATE(paladin);
	UPDATE(firemage);
	UPDATE(holypriest);
	UPDATE(armswarrior);
	UPDATE(marksmanshiphunter);
	
	UPDATE(particle);

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
		}

		if (KEY_PRESS('K'))
		{
			if (targetMonster != nullptr)
				skill->UseSkill(targetMonster->GetCollider());
		}
	}

	player->Update();
	skill->Update();
	MONSTER->Update();

	for (CH_Base_ver2* ch : NPC)
		if (ch != nullptr) ch->Update();
}

void KimScene::PreRender()
{

}

void KimScene::Render()
{
	RENDER(paladin);
	RENDER(firemage);
	RENDER(holypriest);
	RENDER(armswarrior);
	RENDER(marksmanshiphunter);
	RENDER(particle);

	//player->Render();
	skill->Render();
	MONSTER->Render();
	for (CH_Base_ver2* ch : NPC)
		if (ch != nullptr) ch->Render();
}

void KimScene::PostRender()
{
	player->UIRender();
}

void KimScene::GUIRender()
{

}

void KimScene::spawn(ModelAnimatorInstancing* firemage)
{
	Transform* transform1 = firemage->Add();

	CH_Base_ver2* ppp;
	ppp = new ProtectionWarrior_in(CreatureType::NonPlayer, transform1, firemage, count);
	if (firemage == this->firemage)
	{
		ppp = nullptr;
		ppp = new FireMage_in(CreatureType::NonPlayer, transform1, firemage, count);
	}
	if (firemage == holypriest)
	{
		ppp = nullptr;
		ppp = new HolyPriest_in(CreatureType::NonPlayer, transform1, firemage, count);
	}
	if (firemage == armswarrior)
	{
		ppp = nullptr;
		ppp = new ArmsWarrior_in(CreatureType::NonPlayer, transform1, firemage, count);
	}
	if (firemage == marksmanshiphunter)
	{
		ppp = nullptr;
		ppp = new MarksmanshipHunter_in(CreatureType::NonPlayer, transform1, firemage, count);
	}

	if (ppp != nullptr)
		ppp->SetPlayer(player);
	NPC.push_back(ppp);
	count++;
}

void KimScene::instacning01()
{
	paladin = new ModelAnimatorInstancing("ProtectionWarrior");
	paladin->ReadClip("Idle_1");
	paladin->ReadClip("Attack_1");
	paladin->ReadClip("Walk_F");
	paladin->ReadClip("Walk_B");
	paladin->ReadClip("Walk_L");
	paladin->ReadClip("Walk_R");
	paladin->ReadClip("Die");
	paladin->ReadClip("Hit");
	paladin->ReadClip("Jump");
	paladin->ReadClip("S_Casting");
}

void KimScene::instacning02()
{
	firemage = new ModelAnimatorInstancing("FireMage");
	firemage->ReadClip("Idle_1");
	firemage->ReadClip("Idle_2");
	firemage->ReadClip("Attack_1");
	firemage->ReadClip("Attack_2");
	firemage->ReadClip("Attack_3");
	firemage->ReadClip("Walk_F");
	firemage->ReadClip("Walk_B");
	firemage->ReadClip("Walk_L");
	firemage->ReadClip("Walk_R");
	firemage->ReadClip("Die_1");
	firemage->ReadClip("Hit_1");
	firemage->ReadClip("Jump");
}

void KimScene::instacning03()
{
	holypriest = new ModelAnimatorInstancing("HolyPriest");
	holypriest->ReadClip("Idle_1");
	holypriest->ReadClip("Idle_2");
	holypriest->ReadClip("Idle_3");
	holypriest->ReadClip("Attack_1");
	holypriest->ReadClip("Attack_2");
	holypriest->ReadClip("Walk_F");
	holypriest->ReadClip("Walk_B");
	holypriest->ReadClip("Walk_L");
	holypriest->ReadClip("Walk_R");
	holypriest->ReadClip("Die");
	holypriest->ReadClip("Hit");
	holypriest->ReadClip("Jump");
}

void KimScene::instacning04()
{
	armswarrior = new ModelAnimatorInstancing("armswarrior");
	armswarrior->ReadClip("Idle_1");
	armswarrior->ReadClip("Idle_2");
	armswarrior->ReadClip("Attack_1");
	armswarrior->ReadClip("Attack_2");
	armswarrior->ReadClip("Walk_F");
	armswarrior->ReadClip("Walk_B");
	armswarrior->ReadClip("Walk_L");
	armswarrior->ReadClip("Walk_R");
	armswarrior->ReadClip("Die");
	armswarrior->ReadClip("Hit");
	armswarrior->ReadClip("Jump");
}

void KimScene::instacning05()
{
	marksmanshiphunter = new ModelAnimatorInstancing("MarksmanshipHunter");
	marksmanshiphunter->ReadClip("Idle");
	marksmanshiphunter->ReadClip("Attack_1");
	marksmanshiphunter->ReadClip("Walk_F");
	marksmanshiphunter->ReadClip("Walk_B");
	marksmanshiphunter->ReadClip("Walk_L");
	marksmanshiphunter->ReadClip("Walk_R");
	marksmanshiphunter->ReadClip("Die");
	marksmanshiphunter->ReadClip("Hit");
	marksmanshiphunter->ReadClip("Jump");
	marksmanshiphunter->ReadClip("S_Dive");
	marksmanshiphunter->ReadClip("S_Shooting");
}