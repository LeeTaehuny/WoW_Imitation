#include "Framework.h"
#include "P_034_Moment_Of_Glory.h"

P_034_Moment_Of_Glory::P_034_Moment_Of_Glory() : ActiveSkill(SkillType::Target)
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

		// ��Ÿ�� ����
		MAX_delay = 90.0f;
		coolTime = MAX_delay;

		// ó���� ��ų �������� ���°� �ƴϵ��� ����
		isRun = false;
		isCooldown = false;
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/034.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "013";
	prevSkills[1] = "024";
}

P_034_Moment_Of_Glory::~P_034_Moment_Of_Glory()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
}

void P_034_Moment_Of_Glory::Update()
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
}

void P_034_Moment_Of_Glory::Render()
{
}

void P_034_Moment_Of_Glory::UseSkill(CH_Base_ver2* chbase)
{
	if (chbase == nullptr) return;
	targetCharcter = chbase;

	isRun = true;
	isCooldown = true;
}