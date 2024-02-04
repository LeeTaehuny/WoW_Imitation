#include "Framework.h"

SkillBase::SkillBase(SkillType skill)
	: skill(skill)
{

}

SkillBase::~SkillBase()
{
	delete particle;
	delete myCollider;
	delete skillIcon;
}

void SkillBase::SkillUpdate()
{
	switch (skill)
	{
	case SkillBase::TARGET:
		Target();
		break;

	case SkillBase::NONTARGET:
		NonTarget();
		break;
	}

	if (myCollider != nullptr) myCollider->UpdateWorld();
}

void SkillBase::Render()
{
	if (particle != nullptr) particle->Render();
	if (myCollider != nullptr) myCollider->Render();
}

void SkillBase::SkillFire(Vector3 pos)
{
	if (KEY_DOWN(VK_SPACE))
	{
		myCollider->SetActive(true);
		myCollider->Pos() = pos;
	}
}
