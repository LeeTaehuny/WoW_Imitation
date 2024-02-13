﻿#pragma once
#include "Objects/Skills/Base/ActiveSkill.h"

class F_001_Pyroblast : public ActiveSkill
{
public:
	F_001_Pyroblast();
	virtual ~F_001_Pyroblast() override;

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
	ParticleSystem* fireBallParticle;

	bool isPowerUp;

	float delayTime;
	float MAX_delayAnim;

	float additiveDamage;
};

