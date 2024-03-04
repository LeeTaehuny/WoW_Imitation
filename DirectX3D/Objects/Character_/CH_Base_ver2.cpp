#include "Framework.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/UI/QuickSlot.h"
#include "Objects/Item/Weapon.h"
#include "Objects/UI/StatusUI.h"
#include "Objects/UI/PlayerUI_Bar.h"
#include "Objects/UI/MonsterUI_Bar.h"
#include "CH_Base_ver2.h"

CH_Base_ver2::CH_Base_ver2(CreatureType creatureType, ProfessionType professionType)
	: creatureType(creatureType), professionType(professionType)
{
	switch (this->creatureType)
	{
	case CreatureType::Player:
		inventory = new Inventory(this);
		statusUI = new StatusUI(this);
		quickSlot = new QuickSlot(this);

		// HP/MP Bar 생성
		{
			switch (professionType)
			{
			case ProfessionType::ArmsWarrior:
				playerUI = new PlayerUI_Bar(L"Textures/UI/Icons/A_icon.png");
				break;
			case ProfessionType::FireMage:
				playerUI = new PlayerUI_Bar(L"Textures/UI/Icons/F_icon.png");
				break;
			case ProfessionType::HolyPriest:
				playerUI = new PlayerUI_Bar(L"Textures/UI/Icons/H_icon.png");
				break;
			case ProfessionType::MarksmanshipHunter:
				playerUI = new PlayerUI_Bar(L"Textures/UI/Icons/M_icon.png");
				break;
			case ProfessionType::ProtectionWarrior:
				playerUI = new PlayerUI_Bar(L"Textures/UI/Icons/P_icon.png");
				break;
			}

			playerUI->Pos() = { CENTER_X / 3, CENTER_Y + CENTER_Y * 0.7f };
			playerUI->Scale() = { 1.5f, 1.5f, 1.0f };
			playerUI->SetHpPercent(1.0f);
			playerUI->SetMpPercent(1.0f);
		}
		
		// 몬스터 HP bar 생성
		{
			monsterUI = new MonsterUI_Bar();

			monsterUI->Pos() = { CENTER_X + CENTER_X * 2 / 3 , CENTER_Y + CENTER_Y * 0.7f };
			monsterUI->Scale() = { 1.0f, 1.0f, 1.0f };
		}

		break;
	case CreatureType::NonPlayer:
		break;
	}

	mainHand = new Transform();
	mainHand->SetParent(this);
}

CH_Base_ver2::~CH_Base_ver2()
{
	SAFE_DEL(inventory);
}

void CH_Base_ver2::Update()
{
	if (inventory != nullptr) inventory->Update();
	if (statusUI != nullptr) statusUI->Update();
	if (quickSlot != nullptr) quickSlot->Update();
	if (playerUI != nullptr) playerUI->Update();
	if (targetMonster != nullptr && monsterUI != nullptr)
	{
		monsterUI->SetHpPercent(targetMonster->GetHpPercent());
		monsterUI->Update();
	}

	if (weapon != nullptr)
	{
		mainHand->SetWorld(instancing->GetTransformByNode(index, mainHandBoneIndex));
		mainHand->GlobalPos() = GlobalPos();
	
		weapon->Update();
	}

	for (SkillBase* skill : skillList)
	{
		skill->Update();
	}

	// 씬에서 몬스터나 캐릭터의 정보를 얻기 위한 코드
	if (KEY_DOWN(VK_RBUTTON))
	{
		/* 마우스 좌클릭시 Ray 충돌을 통해 몬스터의 정보를 받아옴 */ 
		Ray ray = CAM->ScreenPointToRay(mousePos);
		Contact contact;

		// 몬스터 정보 (리치왕 포함)
		{
			vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
			vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
			vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();
			vector<MonsterBase*> cols4 = MONSTER->GetVAlkier();
			MonsterBase* cols5 = MONSTER->GetLichKing();
			vector<MonsterBase*> cols6 = MONSTER->GetIceBall();

			for (MonsterBase* monster : cols1)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					targetMonster = monster;
					break;
				}
			}
			for (MonsterBase* monster : cols2)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					targetMonster = monster;
					break;
				}
			}
			for (MonsterBase* monster : cols3)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					targetMonster = monster;
					break;
				}
			}
			for (MonsterBase* monster : cols4)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					targetMonster = monster;
					break;
				}
			}
			if (cols5)
			{
				if (cols5->GetCollider()->IsRayCollision(ray, &contact))
				{
					targetMonster = cols5;
				}
			}
			for (MonsterBase* monster : cols6)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					targetMonster = monster;
					break;
				}
			}
		}

		// 캐릭터 정보
		{
			vector<CH_Base_ver2*> player = CH->GetCharcterData();

			for (CH_Base_ver2* p : player)
			{
				if (p == this) continue;

				if (p->GetCollider()->IsRayCollision(ray, &contact))
				{
					targetCharacter = p;
					break;
				}
			}
		}
	}

	if (targetMonster != nullptr)
	{
		// 몬스터의 트랜스폼이 비활성화 되었는가? (죽었다는 의미)
		if (!targetMonster->GetTransform()->Active())
		{
			// 몬스터가 죽었을 경우 해당 변수에 nullptr을 할당
			targetMonster = nullptr;
		}
		// 타겟 몬스터와 일정범위 이상 멀어질 경우
		else if ((targetMonster->GetTransform()->GlobalPos() - this->GlobalPos()).Length() >= 30.0f)
		{
			// 해당 변수에 nullptr 할당
			targetMonster = nullptr;
		}
	}
}

void CH_Base_ver2::Render()
{
	if (weapon != nullptr)
	{
		weapon->Render();
	}

	for (SkillBase* skill : skillList)
	{
		skill->Render();
	}
}

void CH_Base_ver2::UIRender()
{
	if (!Active()) return;
	if (statusUI != nullptr) statusUI->UIRender();
	if (inventory != nullptr) inventory->UIRender();
	if (quickSlot != nullptr) quickSlot->UIRender();
	if (playerUI != nullptr) playerUI->PostRender();
	if (targetMonster != nullptr && monsterUI != nullptr && targetMonster->GetMonsterType() == MonsterType::MON) monsterUI->PostRender();
}

bool CH_Base_ver2::LearnSkill(SkillBase* skill)
{
	if (skill == nullptr) return false;

	// ��ų�� ���ེų�� ��������
	vector<string> prev = skill->GetPrevSkills();

	for (string p : prev)
	{
		// �ش� ��ų�� ���� ��ų�� �̹� ��� ��ų ��Ͽ� �������� �ʴ´ٸ�?
		if (prevSkills.find(p) == prevSkills.end())
		{ 
			// ����
			return false;
		}
	}

	// ������� ���� ��ų�� ��� �� �ִٴ� �ǹ�
	// * ��ų�� ���� �нú� ��ų�̶��?
	if (skill->GetSkillType() == SkillBaseType::Passive)
	{
		// �ٷ� ��ų ���
		skill->UseSkill();
	}

	// ��ų ����Ʈ�� �߰�
	skill->SetOwner(this);
	skillList.push_back(skill);

	// ��� �̸� ����Ʈ�� �ش� ��ų�� �̸� �߰�
	prevSkills.insert({ skill->GetSkillName(), 0 });
}

void CH_Base_ver2::AddHp(int amount)
{
	stat.hp += amount;
	
	if (stat.hp > stat.maxHp)
	{
		stat.hp = stat.maxHp;
	}
}

void CH_Base_ver2::AddMp(int amount)
{
	stat.mp += amount;

	if (stat.mp > stat.maxMp)
	{
		stat.mp = stat.maxMp;
	}
}

void CH_Base_ver2::ClearWeapon()
{
	if (weapon != nullptr)
	{
		weapon = nullptr;
	}
}
