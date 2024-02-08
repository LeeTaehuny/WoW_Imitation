﻿#pragma once
class SkillBase
{
public:
	SkillBase();
	virtual ~SkillBase();

	virtual void Update() {}
	virtual void Render() {}
	virtual void UseSkill() {}
	virtual void UseSkill(Collider* targetCollider) {}
	virtual void UseSkill(Vector3 direction) {}

	//void Cooldown();

// Getter & Setter
public:
	vector<string> GetPrevSkills() { return prevSkills; }
	void SetOwner(class CH_Base_ver2* owner) { this->owner = owner; }
	class CH_Base_ver2* GetOwner() { return owner; }

protected:
	// 본인의 콜라이더
	//Collider* myCollider;

	// 선행스킬 이름
	vector<string> prevSkills;

	// 해당 스킬을 가지는 플레이어에 대한 정보
	class CH_Base_ver2* owner;

	// 일단 스킵
	Quad* icon;

	// 쿨타임
	//float MAX_delay = 5.0f;
	//float delay = MAX_delay;
	// 지금 쿨타운이 돌고 있는지를 확인하기 위한 변수
	// 참이라면 스킬 사용 불가, 거짓이라면 사용 가능
	//bool isCooldown = false;
	//bool isRun = false;
};