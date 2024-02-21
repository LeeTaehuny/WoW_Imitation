#pragma once
class Lich_003_Summon_Drudge_Ghouls : public Lich_000_Base
{
public:
	Lich_003_Summon_Drudge_Ghouls(Boss_LichKing* lich);
	~Lich_003_Summon_Drudge_Ghouls();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

private:

	int JustOne = 0;

	vector<MonsterBase*> life_skel;
};