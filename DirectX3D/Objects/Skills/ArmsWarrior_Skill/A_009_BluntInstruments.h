#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class A_009_BluntInstruments : public PassiveSkill
{
public:
	A_009_BluntInstruments();
	virtual ~A_009_BluntInstruments() override;

	virtual void UseSkill() override;
private:
};

