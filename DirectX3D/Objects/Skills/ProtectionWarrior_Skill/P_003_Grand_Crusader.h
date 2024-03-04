#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class P_003_Grand_Crusader : public PassiveSkill
{
public:
	P_003_Grand_Crusader();
	~P_003_Grand_Crusader();

	virtual void UseSkill() override;
};