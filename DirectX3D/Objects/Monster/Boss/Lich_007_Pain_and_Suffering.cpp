#include "Framework.h"
#include "Lich_007_Pain_and_Suffering.h"

Lich_007_Pain_and_Suffering::Lich_007_Pain_and_Suffering(Boss_LichKing* lich)
{
	this->lich = lich;

	MAX_delay = 120;
	coolTime = MAX_delay;

	Max_animStart = 0.45f;
	isCooldown = false;
}

Lich_007_Pain_and_Suffering::~Lich_007_Pain_and_Suffering()
{
}

void Lich_007_Pain_and_Suffering::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;
	}
}

void Lich_007_Pain_and_Suffering::Render()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;
	}
}

void Lich_007_Pain_and_Suffering::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown) return;

	isRun = true;
	isCooldown = true;
	animStart = 0;
}