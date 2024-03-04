#pragma once
#include "Objects/Skills/Base/ActiveSkill.h"

class A_004_DiebytheSword : public ActiveSkill
{
public:
	A_004_DiebytheSword();
	virtual ~A_004_DiebytheSword() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

private:
	ParticleSystem* particle;

	// 지속 시간
	float curTime;
	float MAX_duration;
};

