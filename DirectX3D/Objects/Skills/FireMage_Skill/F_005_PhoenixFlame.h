#pragma once
#include "Objects/Skills/Base/ActiveSkill.h"

class F_005_PhoenixFlame : public ActiveSkill
{
public:
	F_005_PhoenixFlame();
	virtual ~F_005_PhoenixFlame() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(Collider* targetCollider) override;

// Getter & Setter
public:
	void SetCooltime(float value) { MAX_delay = value; coolTime = value; }
	float GetCooltime() { return coolTime; }

	void SetDamage(float value) { skillDamage = value; }
	float GetDamage() { return skillDamage; }

private:
	ParticleSystem* hitParticleSystem;
	Transform* startEdge;
	Transform* endEdge;

	Trail* trail;

	bool particlePlay = false;
};



