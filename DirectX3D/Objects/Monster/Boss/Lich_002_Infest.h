#pragma once
class Lich_002_Infest : public Lich_000_Base
{
public:
	Lich_002_Infest(Boss_LichKing* lich);
	~Lich_002_Infest();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

private:
	Collider* hitCollider;

};