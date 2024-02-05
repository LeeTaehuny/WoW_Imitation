#include "Framework.h"

SkillBase::SkillBase()
{

}

SkillBase::~SkillBase()
{
	delete myCollider;
	delete particle;
	delete particleSystem;
}