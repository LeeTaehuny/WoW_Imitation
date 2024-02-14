#pragma once
class H_000_Basic_Atttack : public ActiveSkill
{
public:
	H_000_Basic_Atttack();
	~H_000_Basic_Atttack();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

private:
	ParticleSystem* particle;
	MonsterBase* targetMonster;

	float Max_animStart = 0.9f;
	float animStart = 0;
};