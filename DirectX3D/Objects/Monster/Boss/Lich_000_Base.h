#pragma once
class Lich_000_Base
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) = 0;

	void Cooldown();

	bool GetCoolTime() { return isCooldown; }
	bool GetisRun() { return isRun; }

protected:
	Boss_LichKing* lich;

	bool isRun = false;
	bool isCooldown = false;

	float MAX_delay;
	float coolTime;

	float Max_animStart;
	float animStart;
};