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

	// ���� ���� (�ӽ�)
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

	// �ӽ� ���� �ڵ�
	if (KEY_DOWN(VK_LBUTTON))
	{
		// ���콺 ��ġ�� Ray ����
		Ray ray = CAM->ScreenPointToRay(mousePos);
		Contact contact;

		// ���� ����
		{
			// ���� �迭 �ޱ�
			vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
			vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
			vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();

			// ���� ��ȸ�ϸ� Ray �浹 ����
			for (MonsterBase* monster : cols1)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					// �浹�ߴٸ� �ش� ���͸� �� Ÿ������ ����
					targetMonster = monster;
					break;
				}
			}

			for (MonsterBase* monster : cols2)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					// �浹�ߴٸ� �ش� ���͸� �� Ÿ������ ����
					targetMonster = monster;
					break;
				}
			}

			for (MonsterBase* monster : cols3)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					// �浹�ߴٸ� �ش� ���͸� �� Ÿ������ ����
					targetMonster = monster;
					break;
				}
			}
		}

		// TODO : �÷��̾� ����
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
