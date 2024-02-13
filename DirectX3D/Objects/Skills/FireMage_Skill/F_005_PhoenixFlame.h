#pragma once
#include "Objects/Skills/Base/ActiveSkill.h"

class F_005_PhoenixFlame : public ActiveSkill
{
public:
	F_005_PhoenixFlame();
	virtual ~F_005_PhoenixFlame() override;

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
	Transform* startEdge;
	Transform* endEdge;

	Trail* trail;

	bool isPowerUp;

	float delayTime;
	float MAX_delayAnim;

	float additiveDamage;
};



