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

		if (JustOne == 0)
		{
			JustOne++;
			Vector3 lichPos = lich->Pos();
			lichPos.z -= 5;
			lichPos.x -= 5;
			MONSTER->SpawnSkeleton(lichPos);
			life_skel[0] = MONSTER->GetSkeleton()[MONSTER->GetSkeleton().size() - 1];
			lichPos.z += 10;
			MONSTER->SpawnSkeleton(lichPos);
			life_skel[1] = MONSTER->GetSkeleton()[MONSTER->GetSkeleton().size() - 1];
			lichPos.x += 10;
			MONSTER->SpawnSkeleton(lichPos);
			life_skel[2] = MONSTER->GetSkeleton()[MONSTER->GetSkeleton().size() - 1];
			lichPos.z -= 10;
			MONSTER->SpawnSkeleton(lichPos);
			life_skel[3] = MONSTER->GetSkeleton()[MONSTER->GetSkeleton().size() - 1];
		}
		int lifeCount = 0;

		for (int i = 0; i < life_skel.size(); i++)
		{
			if (life_skel[i]->GetTransform()->Active())
			{
				lifeCount++;
			}
		}

		if (lifeCount == 0)
		{
			JustOne = 0;
			isRun = false;
		}
	}

	if (isCooldown && !isRun)
		Lich_000_Base::Cooldown();
}

void Lich_003_Summon_Drudge_Ghouls::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;
	}
}

void Lich_003_Summon_Drudge_Ghouls::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown) return;

	isRun = true;
	isCooldown = true;
	animStart = 0;
}