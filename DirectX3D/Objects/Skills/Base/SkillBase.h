#pragma once
class SkillBase
{
public:
	SkillBase();
	virtual ~SkillBase();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void UseSkill(Vector3 pos) = 0;

	virtual void SetEnemy(Collider* enemy) = 0;

	Particle* particle;
protected:
	// 본인의 콜라이더
	Collider* myCollider;

	// 스킬 파티클
	ParticleSystem* particleSystem;
};