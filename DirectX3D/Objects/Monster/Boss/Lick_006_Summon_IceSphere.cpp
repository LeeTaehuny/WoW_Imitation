#include "Framework.h"
#include "Lick_006_Summon_IceSphere.h"

Lick_006_Summon_IceSphere::Lick_006_Summon_IceSphere(Boss_LichKing* lich)
{
	this->lich = lich;

	MAX_delay = 20;
	coolTime = MAX_delay;

	Max_animStart = 0.45f;
	isCooldown = true;
}

Lick_006_Summon_IceSphere::~Lick_006_Summon_IceSphere()
{
}

void Lick_006_Summon_IceSphere::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		if (JustOne == 0)
		{
			JustOne++;
			Vector3 lichPos = lich->GetTransform()->Pos();
			lichPos.x -= 5;
			MONSTER->SpawnIceBall(lichPos);
		}
	}

	if (isCooldown)
		Lich_000_Base::Cooldown();
}

void Lick_006_Summon_IceSphere::Render()
{
}

void Lick_006_Summon_IceSphere::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown) return;

	isRun = true;
	isCooldown = true;
	animStart = 0;
}