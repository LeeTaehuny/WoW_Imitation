#pragma once
class SkillBase
{
public:
	SkillBase();
	virtual ~SkillBase();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void UseSkill(Vector3 pos) = 0;

	void Cooldown();

	vector<string> GetPrevSkills() { return prevSkills; }

protected:
	// 본인의 콜라이더
	Collider* myCollider;

	// 선행스킬 이름
	vector<string> prevSkills;

	// 쿨타임
	float MAX_delay = 5.0f;
	float delay = MAX_delay;
	// 지금 쿨타운이 돌고 있는지를 확인하기 위한 변수
	// 참이라면 스킬 사용 불가, 거짓이라면 사용 가능
	bool isCooldown = false;
	bool isRun = false;
};