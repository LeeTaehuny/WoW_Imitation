#pragma once
#include "Objects/Skills/Base/ActiveSkill.h"

class A_001_MortalStrike : public ActiveSkill
{
public:
	A_001_MortalStrike();
	virtual ~A_001_MortalStrike() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

// Getter & Setter
public:
	void SetCooltime(float value) { MAX_delay = value; coolTime = value; }
	float GetCooltime() { return coolTime; }

	void SetDamage(float value) { additiveDamage += value; }
	float GetDamage() { return additiveDamage; }

public:
	virtual void Init() override;

private:
	ParticleSystem* hitParticleSystem;
	Transform* startEdge;
	Transform* endEdge;

	Trail* trail;

	float curTime;
	float duration;

	vector<MonsterBase*> hit;

	float additiveDamage;
};

