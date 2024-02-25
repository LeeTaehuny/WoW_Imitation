#pragma once
class Lich_007_Pain_and_Suffering : public Lich_000_Base
{
public:
	Lich_007_Pain_and_Suffering(Boss_LichKing* lich);
	~Lich_007_Pain_and_Suffering();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

private:
};