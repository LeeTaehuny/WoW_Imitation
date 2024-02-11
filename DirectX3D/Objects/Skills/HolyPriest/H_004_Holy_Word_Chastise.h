#pragma once
class H_004_Holy_Word_Chastise : public ActiveSkill
{
public:
	H_004_Holy_Word_Chastise();
	~H_004_Holy_Word_Chastise();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

private:
	ParticleSystem* particle;

	MonsterBase* targetMonster;
};