#include "Framework.h"
#include "Lich_007_Defile.h"

Lich_007_Defile::Lich_007_Defile(Boss_LichKing* lich)
{
	hitCollider = new SphereCollider();

	particle = new Quad(L"TextData/Particles/LichKing/lich_skill007.png");
	particle->Scale() *= 0.02f;
	particle->Rot().x = XM_PI * 0.5f;
	particle->SetParent(hitCollider);
	
	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	this->lich = lich;
	MAX_delay = 5;
	coolTime = MAX_delay;

	Max_animStart = 0.45f;
	isCooldown = true;

	conh = CH->GetCharcterData();
}

Lich_007_Defile::~Lich_007_Defile()
{
	delete particle;
	delete hitCollider;

	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void Lich_007_Defile::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		runTime -= DELTA;
		tickTime -= DELTA;
		if (runTime <= 0)
		{
			runTime = Max_runTime;
			isRun = false;
			return;
		}
		if (tickTime <= 0)
		{
			tickTime = Max_tickTime;
			for (CH_Base_ver2* ch : conh)
			{
				if (hitCollider->IsCollision(ch->GetCollider()))
				{
					ch->OnHit(lich->GetStat().damage * vaUl, true);
					vaUl += 0.05f;
					hitCollider->Scale().x += 5 * DELTA;
					hitCollider->Scale().z += 5 * DELTA;
				}
			}
		}

		hitCollider->UpdateWorld();
		particle->Rot().y += DELTA;
		particle->UpdateWorld();
	}

	if (isCooldown && !isRun)
		Lich_000_Base::Cooldown();
}

void Lich_007_Defile::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		blendState[1]->SetState();
		depthState[1]->SetState();
		particle->Render();
		blendState[0]->SetState();
		depthState[0]->SetState();

		hitCollider->Render();
	}
}

void Lich_007_Defile::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown) return;
	characterData = chbase;

	hitCollider->Pos() = characterData->Pos();
	hitCollider->UpdateWorld();
	particle->UpdateWorld();

	MAX_delay = 3;
	coolTime = MAX_delay;

	runTime = Max_runTime;
	tickTime = Max_tickTime;
	isRun = true;
	isCooldown = true;
	animStart = 0;
}