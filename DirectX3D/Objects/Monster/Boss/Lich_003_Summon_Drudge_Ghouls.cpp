#include "Framework.h"
#include "Lich_003_Summon_Drudge_Ghouls.h"

Lich_003_Summon_Drudge_Ghouls::Lich_003_Summon_Drudge_Ghouls(Boss_LichKing* lich)
{
	this->lich = lich;
	MAX_delay = 5;
	coolTime = MAX_delay;

	Max_animStart = 0.45f;
	isCooldown = true;

	life_skel.resize(4);
}

Lich_003_Summon_Drudge_Ghouls::~Lich_003_Summon_Drudge_Ghouls()
{

}

void Lich_003_Summon_Drudge_Ghouls::Update()
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
			lichPos.z -= 5;
			lichPos.x -= 5;
			MONSTER->SpawnSkeleton(lichPos);
			lichPos.z += 10;
			MONSTER->SpawnSkeleton(lichPos);
			lichPos.x += 10;
			MONSTER->SpawnSkeleton(lichPos);
			lichPos.z -= 10;
			MONSTER->SpawnSkeleton(lichPos);
		}
	}

	if (isCooldown)
		Lich_000_Base::Cooldown();
}

void Lich_003_Summon_Drudge_Ghouls::Render()
{
}

void Lich_003_Summon_Drudge_Ghouls::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown) return;

	MAX_delay = 35;
	coolTime = MAX_delay;
	isRun = true;
	isCooldown = true;
	animStart = 0;
}