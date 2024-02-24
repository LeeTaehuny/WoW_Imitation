#include "Framework.h"
#include "Lich_002_Infest.h"

Lich_002_Infest::Lich_002_Infest(Boss_LichKing* lich)
{
	this->lich = lich;

	hitCollider = new SphereCollider();
	hitCollider->SetParent(lich->GetTransform());
	hitCollider->Scale().x *= 4000;
	hitCollider->Scale().z *= 4000;
	hitCollider->Scale().y *= 200;
}

Lich_002_Infest::~Lich_002_Infest()
{
	delete hitCollider;
}

void Lich_002_Infest::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;
	}

	if (isCooldown)
		Lich_000_Base::Cooldown();
}

void Lich_002_Infest::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;
		hitCollider->Render();
	}
}

void Lich_002_Infest::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown) return;

	isRun = true;
	isCooldown = true;
	animStart = 0;
}