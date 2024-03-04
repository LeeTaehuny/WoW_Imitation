#include "Framework.h"
#include "Lich_000_Base.h"

void Lich_000_Base::Cooldown()
{
	coolTime -= DELTA;

	if (coolTime <= 0)
	{
		coolTime = MAX_delay;
		isCooldown = false;
	}
}