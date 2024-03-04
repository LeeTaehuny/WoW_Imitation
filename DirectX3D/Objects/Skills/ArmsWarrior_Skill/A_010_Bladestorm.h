#pragma once
class A_010_Bladestorm : public ActiveSkill
{
public:
	A_010_Bladestorm();
	virtual ~A_010_Bladestorm() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

public:
	void SetCooltime(float value) { MAX_delay = value; coolTime = value; }
	float GetCooltime() { return coolTime; }

	void SetDamage(float value) { additiveDamage += value; }
	float GetDamage() { return additiveDamage; }

public:
	virtual void Init() override;

private:
	ModelInstancing* sword;
	vector<Transform*> swordTransforms;
	
	// 지속 시간
	float curTime;
	float MAX_duration;

	// 공격 시간(간격)
	float hitTime;
	float MAX_hitTime;

	// 피격당한 몬스터들을 저장하기 위한 벡터
	vector<MonsterBase*> hit;

	float additiveDamage;

	// 사운드 재생 판별 변수
	bool isPlay;
};
