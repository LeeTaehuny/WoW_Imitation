#include "Framework.h"

P_004_HOTR::P_004_HOTR() : ActiveSkill(SkillType::Target)
{
	myCollider = new SphereCollider(2.5f);
	myCollider->SetActive(false);
	hitCollider = new SphereCollider();
	hitCollider->SetActive(true);

	root = new Transform();
	myCollider->SetParent(root);

	// �⺻ ���� ���
	{
		// ��ų �ӵ�
		speed = 0.0f;

		// ��ų ������
		skillDamage = 100.0f;

		// ��Ÿ�� ���� (5��)
		MAX_delay = 5.0f;
		coolTime = MAX_delay;

		// ó���� ��ų �������� ���°� �ƴϵ��� ����
		isRun = false;
		isCooldown = false;
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/004.jpg");
}

P_004_HOTR::~P_004_HOTR()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete root;
}

void P_004_HOTR::Update()
{
	// ���⸦ �� ������ �ݶ��̴��� ����
	if (hitCollider->Active())
	{
		// �׳� ������ �ϸ� ���� �����θ� ���� Ŀ���� 3�� �࿡ ���� ����
		float ful = 10.5f; // �� ������ ���� �ϱ� ���� ����
		hitCollider->Scale().x += ful * DELTA;
		//hitCollider->Scale().y += ful * DELTA;
		hitCollider->Scale().z += ful * DELTA;

		if (hitCollider->Scale().x >= 7)
		{
			hitCollider->SetActive(false);
		}
	}
	else
	{
		//hitCollider->Scale() = Vector3(0.01f, 0.01f, 0.01f);
	}

	root->SetWorld(owner->GetInstancing()->GetTransformByNode(owner->GetIndex(), 38));
	
	//myCollider->GlobalPos() = root->Pos();
	myCollider->UpdateWorld();
	hitCollider->UpdateWorld();
}

void P_004_HOTR::Render()
{
	myCollider->Render();
	hitCollider->Render();
}

void P_004_HOTR::UseSkill(Collider* targetCollider)
{
	if (targetCollider == nullptr) return;
	target = targetCollider;

	myCollider->SetActive(true);
	//myCollider->Pos() = owner->GlobalPos();

	// ������ ��ų ��� ���� �����ϴ� ������ ������
	// ���߿��� ���� ����� ������ ������ �޴� ������ ���� �ؾ� ��
	if (target->IsCollision(myCollider))
	{
		hitCollider->SetActive(true);
		hitCollider->Pos() = target->Pos();
		isRun = true;
		isCooldown = true;
	}
}
