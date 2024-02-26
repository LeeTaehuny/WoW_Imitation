#include "Framework.h"
#include "Lick_008_Summon_Dark_Valkyr.h"

Lick_008_Summon_Dark_Valkyr::Lick_008_Summon_Dark_Valkyr(Boss_LichKing* lich)
{
	this->lich = lich;

	MAX_delay = 20;
	coolTime = MAX_delay;

	Max_animStart = 0.45f;
	isCooldown = true;
}

Lick_008_Summon_Dark_Valkyr::~Lick_008_Summon_Dark_Valkyr()
{
}

void Lick_008_Summon_Dark_Valkyr::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		MONSTER->SpawnVAlkier(lich->GetTransform()->Pos());

		isRun = false;
		return;
	}

	if (isCooldown)
		Lich_000_Base::Cooldown();
}

void Lick_008_Summon_Dark_Valkyr::Render()
{
}

void Lick_008_Summon_Dark_Valkyr::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown) return;

	MAX_delay = 60;
	coolTime = MAX_delay;

	isRun = true;
	isCooldown = true;
	animStart = 0;
}