#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class P_008_Guardian_Of_Ancient_Kings : public PassiveSkill
{
public:
	P_008_Guardian_Of_Ancient_Kings();
	~P_008_Guardian_Of_Ancient_Kings();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};