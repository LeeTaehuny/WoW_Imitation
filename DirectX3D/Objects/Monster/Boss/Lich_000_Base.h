#pragma once
class Lich_000_Base
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	// 스킬을 사용할때 사용하기 위한 변수
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) = 0;

	// 쿨타임을 돌리기 위한 함수
	void Cooldown();

	// 현재 쿨타임 변수의 값을 얻기 위한 함수
	bool GetCoolTime() { return isCooldown; }
	// 현재 스킬이 작동중인지 값을 얻기 위한 함수
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