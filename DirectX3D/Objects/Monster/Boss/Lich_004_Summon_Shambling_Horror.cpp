#include "Framework.h"
#include "Lich_004_Summon_Shambling_Horror.h"

Lich_004_Summon_Shambling_Horror::Lich_004_Summon_Shambling_Horror(Boss_LichKing* lich)
{
	this->lich = lich;
	MAX_delay = 20;
	coolTime = MAX_delay;

	Max_animStart = 0.45f;
	isCooldown = true;
}

Lich_004_Summon_Shambling_Horror::~Lich_004_Summon_Shambling_Horror()
{
}

void Lich_004_Summon_Shambling_Horror::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		// 한 번만 스폰하게하기 위한 작업
		if (JustOne == 0)
		{
			JustOne++;
			Vector3 lichPos = lich->GetTransform()->Pos();
			lichPos.x -= 5;
			MONSTER->SpawnSkeletonKnight(lichPos);
		}
	}

	if (isCooldown)
		Lich_000_Base::Cooldown();
}

void Lich_004_Summon_Shambling_Horror::Render()
{
}

void Lich_004_Summon_Shambling_Horror::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown) return;

	MAX_delay = 90;
	coolTime = MAX_delay;

	isRun = true;
	isCooldown = true;
	animStart = 0;
	JustOne = 0;
}