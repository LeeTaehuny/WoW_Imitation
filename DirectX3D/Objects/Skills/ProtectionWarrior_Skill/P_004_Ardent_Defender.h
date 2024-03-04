#pragma once
#include "Objects/Skills/Base/PassiveSkill.h"

class P_004_Ardent_Defender : public PassiveSkill
{
public:
	P_004_Ardent_Defender();
	~P_004_Ardent_Defender();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;
};