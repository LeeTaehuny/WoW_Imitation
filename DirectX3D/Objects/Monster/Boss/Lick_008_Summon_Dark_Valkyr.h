#pragma once
class Lick_008_Summon_Dark_Valkyr : public Lich_000_Base
{
public:
	Lick_008_Summon_Dark_Valkyr(Boss_LichKing* lich);
	~Lick_008_Summon_Dark_Valkyr();

	virtual void Update() override;
	virtual void Render() override;
	// 스킬 사용에 쓰기 위한 함수
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

private:
	int JustOne = 0;

};