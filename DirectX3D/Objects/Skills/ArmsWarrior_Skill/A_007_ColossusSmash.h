#pragma once
#include "Objects/Skills/Base/ActiveSkill.h"

class A_007_ColossusSmash : public ActiveSkill
{
public:
	A_007_ColossusSmash();
	virtual ~A_007_ColossusSmash() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

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
	ParticleSystem* swordBallParticle;

	float delayTime;
	float MAX_delayAnim;

	float additiveDamage;
};

