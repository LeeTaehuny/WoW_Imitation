#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class P_007_Blessing_of_Spellwarding : public PassiveSkill
{
public:
	P_007_Blessing_of_Spellwarding();
	~P_007_Blessing_of_Spellwarding();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};