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
	attackTarget_serch->Scale() *= 300;

	// ���� ���Ϳ� ���� ����� ĳ���͸� �Ǻ��ϱ� ���� �κ�
	{
		attackTarget_serch->UpdateWorld();
		float atk_leng = FLT_MAX;
		vector<CH_Base_ver2*> characterData = CH->GetCharcterData();
		CH_Base_ver2* lom = target[0];
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
		targetTransform = lom;
	}
	hitText.resize(20);

	// �������� ���� ����
	maxHP = 500.0f;
	curHP = maxHP;
	Atk = 10.0f;

	// ù ��° ��ų
	{
		particle = new ParticleSystem("TextData/Particles/LichKing/iceball/ice01.fx");
		nomarATK = new SphereCollider();
	}
}

IceBall::~IceBall()
{
	delete collider;
	delete attackRange;
	delete root;
	delete targetTransform;
	delete attackBumwe;
	delete attackTarget_serch;
	delete particle;
	delete nomarATK;
}

void IceBall::Update()
{
	if (!transform->Active()) return;
	if (curHP <= 0)
	{
		transform->SetActive(false);
		collider->SetActive(false);
		return;
	}

	Move();
	targetAttack();
	MonsterBase::targetActiveSerch();

	iceball->UpdateWorld();
	collider->UpdateWorld();
	attackRange->UpdateWorld();
}

void IceBall::Render()
{
	if (!transform->Active()) return;
	iceball->Render();
	collider->Render();
	attackRange->Render();
	nomarATK->Render();

	if (particle->IsPlay())
		particle->Render();
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
		Audio::Get()->Play("iceBall_die", transform->Pos(), 1.0f);
	}
	else
	{
		Audio::Get()->Play("iceBall_hit", transform->Pos(), 1.0f);
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
	transform->Pos().y = 3;
	transform->Rot().y = atan2(velocity.x, velocity.z) + XM_PI;
	transform->UpdateWorld();
}

void IceBall::targetAttack()
{
	if (!targetTransform) return;

	if (particle->IsPlay())
	{
		particle->SetPos(targetTransform->Pos());
		particle->Update();
	}
	else
	{
		particle->Play(Vector3());
	}

	tickTime -= DELTA;
	if (tickTime <= 0)
	{
		tickTime = Max_tickTime;
		nomarATK->Pos() = targetTransform->Pos();
		nomarATK->UpdateWorld();
		for (CH_Base_ver2* ch : CH->GetCharcterData())
		{
			if (nomarATK->IsCollision(ch->GetCollider()))
			{
				ch->OnHit(Atk, true);
			}
		}
	}
}