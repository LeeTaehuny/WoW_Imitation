#include "Framework.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Item/Weapon.h"
#include "Objects/UI/StatusUI.h"
#include "CH_Base_ver2.h"

CH_Base_ver2::CH_Base_ver2(CreatureType creatureType, ProfessionType professionType)
	: creatureType(creatureType), professionType(professionType)
{
	switch (this->creatureType)
	{
	case CreatureType::Player:
		inventory = new Inventory();
		statusUI = new StatusUI(this);
		break;
	case CreatureType::NonPlayer:
		break;
	}

	// ���� ���� (�ӽ�)
	stat.maxHp = 1000.0f;
	stat.hp = stat.maxHp;
	stat.maxMp = 1000;
	stat.mp = stat.maxMp;
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

	if (weapon != nullptr)
	{
		mainHand->SetWorld(instancing->GetTransformByNode(index, mainHandBoneIndex));
		mainHand->GlobalPos() = GlobalPos();

		weapon->Update();
	}
}

void CH_Base_ver2::Render()
{
	if (weapon != nullptr)
	{
		weapon->Render();
	}
}

void CH_Base_ver2::UIRender()
{
	if (!Active()) return;
	if (statusUI != nullptr) statusUI->UIRender();
	if (inventory != nullptr) inventory->UIRender();
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
	skillList.push_back(skill);

	// ��� �̸� ����Ʈ�� �ش� ��ų�� �̸� �߰�
	prevSkills.insert({ skill->GetSkillName(), 0 });
}

void CH_Base_ver2::ClearWeapon()
{
	if (weapon != nullptr)
	{
		weapon = nullptr;
	}
}
