#include "Framework.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/UI/QuickSlot.h"
#include "Objects/Item/Weapon.h"
#include "Objects/UI/StatusUI.h"
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
		break;
	case CreatureType::NonPlayer:
		break;
	}

	// 스탯 설정 (임시)
	stat.maxHp = 1000.0f;
	stat.hp = 10.0f;//stat.maxHp;
	stat.maxMp = 1000;
	stat.mp = 10.0f;//stat.maxMp;
	stat.damage = 100.0f;
	stat.defence = 100;

	mainHand = new Transform();
	mainHand->SetParent(this);
}

CH_Base_ver2::~CH_Base_ver2()
{
	SAFE_DEL(inventory);
	SAFE_DEL(myPlayer);
}

void CH_Base_ver2::Update()
{
	if (inventory != nullptr) inventory->Update();
	if (statusUI != nullptr) statusUI->Update();
	if (quickSlot != nullptr) quickSlot->Update();

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

	// 임시 지정 코드
	if (KEY_DOWN(VK_LBUTTON))
	{
		// 마우스 위치의 Ray 생성
		Ray ray = CAM->ScreenPointToRay(mousePos);
		Contact contact;

		// 몬스터 선택
		{
			// 몬스터 배열 받기
			vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
			vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
			vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();

			// 몬스터 순회하며 Ray 충돌 연산
			for (MonsterBase* monster : cols1)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					// 충돌했다면 해당 몬스터를 내 타겟으로 설정
					targetMonster = monster;
					break;
				}
			}

			for (MonsterBase* monster : cols2)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					// 충돌했다면 해당 몬스터를 내 타겟으로 설정
					targetMonster = monster;
					break;
				}
			}

			for (MonsterBase* monster : cols3)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					// 충돌했다면 해당 몬스터를 내 타겟으로 설정
					targetMonster = monster;
					break;
				}
			}
		}

		// TODO : 플레이어 선택
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
}

bool CH_Base_ver2::LearnSkill(SkillBase* skill)
{
	if (skill == nullptr) return false;

	// 스킬의 선행스킬들 가져오기
	vector<string> prev = skill->GetPrevSkills();

	for (string p : prev)
	{
		// 해당 스킬의 선행 스킬이 이미 배운 스킬 목록에 존재하지 않는다면?
		if (prevSkills.find(p) == prevSkills.end())
		{ 
			// 종료
			return false;
		}
	}

	// 여기까지 오면 스킬을 배울 수 있다는 의미
	// * 스킬이 만약 패시브 스킬이라면?
	if (skill->GetSkillType() == SkillBaseType::Passive)
	{
		// 바로 스킬 사용
		skill->UseSkill();
	}

	// 스킬 리스트에 추가
	skill->SetOwner(this);
	skillList.push_back(skill);

	// 배운 이름 리스트에 해당 스킬의 이름 추가
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
