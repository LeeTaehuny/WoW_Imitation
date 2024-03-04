#pragma once
class Lick_006_Summon_IceSphere : public Lich_000_Base
{
public:
	Lick_006_Summon_IceSphere(Boss_LichKing* lich);
	~Lick_006_Summon_IceSphere();

	virtual void Update() override;
	virtual void Render() override;
	// 스킬 사용에 쓰기 위한 함수
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

private:

	int JustOne = 0;

	MonsterBase* life_skel;
};