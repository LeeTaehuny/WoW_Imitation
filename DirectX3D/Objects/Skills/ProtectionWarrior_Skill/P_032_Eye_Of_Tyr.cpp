#include "Framework.h"
#include "P_032_Eye_Of_Tyr.h"

P_032_Eye_Of_Tyr::P_032_Eye_Of_Tyr() : ActiveSkill(SkillType::NonTarget)
{
	/*
	��ų�� ȿ��

	���п��� ���� �߻��Ͽ� �������� ��� ������ �ż����ظ� ������ 9�ʰ�
	����� �ڽſ��� ������ ���ظ� 25%��ŭ ���ҽ�Ŵ
	*/

	hitCollider = new SphereCollider();
	hitCollider->SetActive(false);

	// �⺻ ���� ���
	{
		// ��ų �ӵ�
		speed = 0.0f;

		// ��ų ������
		skillDamage = 100.0f;

		// ��Ÿ�� ����
		MAX_delay = 0.0f;
		coolTime = MAX_delay;

		// ó���� ��ų �������� ���°� �ƴϵ��� ����
		isRun = false;
		isCooldown = false;

		// // ���� �Ҹ� �Ҹ� : 0.5%
	}

	// ����Ʈ�� ���� ����?
	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	// ����Ʈ �ؽ�ó
	donut = new Quad(L"Textures/Effect/alpha_gold_donut.png");
	donut->SetParent(hitCollider);
	donut->Scale() *= 0.1;

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/032.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "P_024_Guardian_Of_Ancient_Kings";
}

P_032_Eye_Of_Tyr::~P_032_Eye_Of_Tyr()
{
	delete donut;
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete targetCharcter;

	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void P_032_Eye_Of_Tyr::Update()
{
	//ActiveSkill::Update();

	if (isRun)
	{
		hitCollider->Pos() = owner->GlobalPos();
		 
		vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
		for (MonsterBase* monster : cols1)
		{
			if (hitCollider->IsCollision(monster->GetCollider()))
			{
				// �浹�� ���͵鿡�� ������ �ֱ�
				// * �Ű������� owner�� ���ݷ°� ��ȣ �����ϱ�
				monster->Hit(skillDamage);
			}
		}
		cols1 = MONSTER->GetSkeleton();
		for (MonsterBase* monster : cols1)
		{
			if (hitCollider->IsCollision(monster->GetCollider()))
			{
				// �浹�� ���͵鿡�� ������ �ֱ�
				// * �Ű������� owner�� ���ݷ°� ��ȣ �����ϱ�
				monster->Hit(skillDamage);
			}
		}
		cols1 = MONSTER->GetSkeleton_Knight();
		for (MonsterBase* monster : cols1)
		{
			if (hitCollider->IsCollision(monster->GetCollider()))
			{
				// �浹�� ���͵鿡�� ������ �ֱ�
				// * �Ű������� owner�� ���ݷ°� ��ȣ �����ϱ�
				monster->Hit(skillDamage);
			}
		}

		float ful = 10.5f; // �� ������ ���� �ϱ� ���� ����
		hitCollider->Scale().x += ful * DELTA;
		hitCollider->Scale().y += ful * DELTA;
		hitCollider->Scale().z += ful * DELTA;

		// ��Ʈ ������ ���� ������ �Ѿ�� ��Ƽ�긦 ���鼭 ���� ����
		if (hitCollider->Scale().x >= 7)
		{
			hitCollider->SetActive(false);
			//hitCollider->Scale() = Vector3(1, 1, 1);
			isRun = false;
		}

		donut->Rot() = CAM->Rot();
		donut->UpdateWorld();
		hitCollider->UpdateWorld();
	}
	else if (!isRun)
	{
		hitCollider->Scale() = Vector3(1, 1, 1);
		hitCollider->Pos() = Vector3(0, -50, 0);
		hitCollider->UpdateWorld();
		donut->UpdateWorld();
	}

	ActiveSkill::Cooldown();
}

void P_032_Eye_Of_Tyr::Render()
{
	if (isRun)
	{
		blendState[1]->SetState();
		depthState[1]->SetState();

		donut->Render();

		blendState[0]->SetState();
		depthState[0]->SetState();

		//hitCollider->Render();
	}
}

void P_032_Eye_Of_Tyr::UseSkill()
{
	if (isCooldown) return;

	hitCollider->SetActive(true);
	isRun = true;
	isCooldown = true;
}