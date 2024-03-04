#pragma once
class M_000_Basic_Atttack : public ActiveSkill
{
public:
	M_000_Basic_Atttack();
	~M_000_Basic_Atttack();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

private:
	ParticleSystem* particle;

	Arrow* arrow;
	MonsterBase* targetMonster;

	float Max_animStart = 0.35f;
	float animStart = 0;
};