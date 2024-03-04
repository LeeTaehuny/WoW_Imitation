#pragma once
class Lich_006_Summon_IceSphere : public Lich_000_Base
{
public:
	Lich_006_Summon_IceSphere(Boss_LichKing* lich);
	~Lich_006_Summon_IceSphere();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

private:
};