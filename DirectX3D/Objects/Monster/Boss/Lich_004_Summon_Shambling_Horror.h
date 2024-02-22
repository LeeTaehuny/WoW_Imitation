#pragma once
class Lich_004_Summon_Shambling_Horror : public Lich_000_Base
{
public:
	Lich_004_Summon_Shambling_Horror(Boss_LichKing* lich);
	~Lich_004_Summon_Shambling_Horror();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

private:
	int JustOne = 0;

	MonsterBase* life_skel;
};