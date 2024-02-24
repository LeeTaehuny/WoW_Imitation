#include "Framework.h"
#include "Lich_005_Remorseless_Winter.h"

Lich_005_Remorseless_Winter::Lich_005_Remorseless_Winter(Boss_LichKing* lich)
{
	this->lich = lich;
	MAX_delay = 5000;
	coolTime = MAX_delay;

	Max_animStart = 0.45f;
	isCooldown = false;

	particle = new ParticleSystem("TextData/Particles/LichKing/LichKing_05.fx");
	hitCollider = new SphereCollider();
	hitCollider->Scale().x *= 25;
	hitCollider->Scale().z *= 25;
}

Lich_005_Remorseless_Winter::~Lich_005_Remorseless_Winter()
{
	delete particle;
	delete hitCollider;
}

void Lich_005_Remorseless_Winter::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		if (particle->IsPlay())
		{
			particle->SetPos(lich->GetTransform()->Pos());
			particle->Update();
		}
		else
		{
			particle->Play(Vector3());
		}

		runTime -= DELTA;
		if (runTime <= 0)
		{
			runTime = Max_runTime;
			tickTime = Max_tickTime;
			isRun = false;
			return;
		}

		tickTime -= DELTA;
		if (tickTime <= 0)
		{
			tickTime = Max_tickTime;
			vector<CH_Base_ver2*> conh = CH->GetCharcterData();
			for (CH_Base_ver2* ch : conh)
			{
				if (hitCollider->IsCollision(ch->GetCollider()))
				{
					ch->OnHit(lich->GetStat().damage * 0.1f);
				}
			}
		}
	}
}

void Lich_005_Remorseless_Winter::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		particle->Render();
		hitCollider->Render();
	}
}

void Lich_005_Remorseless_Winter::UseSkill(CH_Base_ver2* chbase)
{
	if (isRun) return;

	isRun = true;
	animStart = 0;

	hitCollider->Pos() = lich->GetTransform()->Pos();
	hitCollider->UpdateWorld();
}