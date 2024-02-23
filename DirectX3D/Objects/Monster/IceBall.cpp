#include "Framework.h"

IceBall::IceBall(vector<CH_Base_ver2*> target)
{
	this->transform = new Transform();
	this->target = target;
	iceball = new Sphere();
	iceball->GetMaterial()->SetDiffuseMap(L"Textures/Model/iceBall/iceshard.png");
	iceball->SetParent(transform);

	collider = new CapsuleCollider();
	collider->SetParent(this->transform);
	attackRange = new SphereCollider(10);
	attackRange->SetParent(this->transform);

	velocity = Vector3();

	attackTarget_serch = new SphereCollider();
	attackTarget_serch->SetParent(this->transform);
	attackTarget_serch->Scale() *= 1200;

	// ���� ���Ϳ� ���� ����� ĳ���͸� �Ǻ��ϱ� ���� �κ�
	{
		attackTarget_serch->UpdateWorld();
		float atk_leng = FLT_MAX;
		vector<CH_Base_ver2*> characterData = CH->GetCharcterData();
		CH_Base_ver2* lom = nullptr;
		for (int i = 0; i < characterData.size(); ++i)
		{
			if (attackTarget_serch->IsCollision(characterData[i]->GetCollider()))
			{
				Vector3 leng = characterData[i]->GlobalPos() - attackTarget_serch->GlobalPos();
				float min = leng.Length();

				if (atk_leng >= min)
				{
					atk_leng = min;
					lom = characterData[i];
				}
			}
		}
		if (lom != nullptr)
		{
			targetTransform = lom;
		}
	}
	hitText.resize(20);

	// �������� ���� ����
	maxHP = 500.0f;
	curHP = maxHP;
	Atk = 10.0f;
}

IceBall::~IceBall()
{
	delete collider;
	delete attackRange;
	delete root;
	delete targetTransform;
	delete attackBumwe;
	delete attackTarget_serch;
}

void IceBall::Update()
{
	if (!transform->Active()) return;

	Move();
	targetAttack();
	MonsterBase::targetActiveSerch();
	//UpdateUI();

	iceball->UpdateWorld();
	collider->UpdateWorld();
	attackRange->UpdateWorld();
}

void IceBall::Render()
{
	iceball->Render();
	collider->Render();
	attackRange->Render();
}

void IceBall::PostRender()
{
	if (!transform->Active()) return;

	for (HitDesc& hit : hitText)
	{
		// ��� Off�� ��� X
		if (!hit.isPrint) continue;

		// ���ӽð� ���� �� ��� ���� üũ
		hit.duration -= DELTA;

		if (hit.duration <= 0.0f)
		{
			hit.isPrint = false;
		}

		// ������ ��ġ ���ϱ�
		Vector3 screenPos = CAM->WorldToScreen(collider->GlobalPos());
		// ��� (���� �ð��� ����ؼ� ���� �ö󰡰� �����ϱ�)
		Font::Get()->RenderText(hit.damage, { screenPos.x + 15.0f , screenPos.y - (50.0f * hit.duration) + 55.0f });
	}
}

void IceBall::Hit(float amount)
{
	curHP -= amount;

	if (curHP <= 0)
	{
		collider->SetActive(false);
		curHP = 0.0f;
	}

	for (int i = 0; i < hitText.size(); i++)
	{
		// ��� off �����̸�
		if (!hitText[i].isPrint)
		{
			// ��� �����ϱ�
			hitText[i].isPrint = true;
			hitText[i].duration = 1.0f;
			hitText[i].damage = to_string((int)amount);

			break;
		}
	}
}

void IceBall::Spawn(Vector3 pos)
{
	transform->SetActive(true);
	collider->SetActive(true);
	curHP = maxHP;
	transform->Pos() = pos;
}

void IceBall::Move()
{
	velocity = (targetTransform->GlobalPos() - transform->GlobalPos()).GetNormalized();

	transform->Pos() += velocity * 2 * DELTA;
	transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
	transform->UpdateWorld();
}

void IceBall::targetAttack()
{
	
}

void IceBall::UpdateUI()
{
}