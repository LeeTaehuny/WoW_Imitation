#pragma once
#include "Objects/Skills/Base/ActiveSkill.h"

class F_009_Combustion : public ActiveSkill
{
public:
	F_009_Combustion();
	virtual ~F_009_Combustion() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

private:
	ParticleSystem* particle;

	// 지속 시간
	float curTime;
	float MAX_duration;
};

