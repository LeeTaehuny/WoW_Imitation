#include "Framework.h"
#include "P_010_Moment_Of_Glory.h"

P_010_Moment_Of_Glory::P_010_Moment_Of_Glory() : ActiveSkill(SkillType::Target)
{
	/*
	��ų�� ȿ��

	15�� ���� ���� ��� ������ 25%�� �ش��ϴ� ���� ��� ��ȣ���� ������

	��¡�� ������ ���ݷ� 20% ��� �� ����ð� 75%��ŭ ����
	*/
	
	// �⺻ ���� ���
	{
		// ��ų �ӵ� (�ʿ� ����)
		speed = 0.0f;

		// ��ų ������
		skillDamage = 0.0f;

		// ��Ÿ�� ���� (�⺻�� 90��)
		MAX_delay = 5.0f;
		coolTime = MAX_delay;

		maxRuntime = 15.0f;
		curRuntime = maxRuntime;

		// ó���� ��ų �������� ���°� �ƴϵ��� ����
		isRun = false;
		isCooldown = false;

		// // ���� �Ҹ� �Ҹ� : 0.5%
		usingType = character_Data;
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/010.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "P_013_Bulwark_Of_Order";
	prevSkills[1] = "P_024_Guardian_Of_Ancient_Kings";
}

P_010_Moment_Of_Glory::~P_010_Moment_Of_Glory()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
}

void P_010_Moment_Of_Glory::Update()
{
	if (isRun)
	{
		curRuntime -= DELTA;
		if (curRuntime <= 0)
		{
			curRuntime = maxRuntime;
			isRun = false;
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void P_010_Moment_Of_Glory::Render()
{
}

void P_010_Moment_Of_Glory::UseSkill(CH_Base_ver2* chbase)
{
	if (chbase == nullptr) return;
	targetCharcter = chbase;

	skillDamage = owner->GetStat().damage;
	isRun = true;
	isCooldown = true;
}