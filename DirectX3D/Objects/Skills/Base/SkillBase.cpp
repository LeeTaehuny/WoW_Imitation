#include "Framework.h"

SkillBase::SkillBase()
{

}

SkillBase::~SkillBase()
{
	delete myCollider;
}

void SkillBase::Cooldown()
{
	delay -= DELTA;
	if (delay <= 0)
	{
		delay = MAX_delay;
		isCooldown = false;
	}
}
