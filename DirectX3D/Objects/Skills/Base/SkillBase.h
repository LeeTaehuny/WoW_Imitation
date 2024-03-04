#pragma once

// 스킬의 타입을 구분하기 위한 열거형
enum class SkillBaseType
{
	Active,
	Passive,
};

class SkillBase
{
public:
	SkillBase(SkillBaseType skillBaseType);
	virtual ~SkillBase();

	virtual void Update() {}
	virtual void Render() {}
	virtual void UseSkill() {}
	virtual void UseSkill(Collider* targetCollider) {}
	virtual void UseSkill(Vector3 direction) {}
	virtual void UseSkill(CH_Base_ver2* chbase) {}
	virtual void UseSkill(MonsterBase* monsterbase) {}

	virtual void Init() {};

// Getter & Setter
public:
	vector<string> GetPrevSkills() { return prevSkills; }
	void SetOwner(class CH_Base_ver2* owner) { this->owner = owner; }
	class CH_Base_ver2* GetOwner() { return owner; }
	Quad* GetIcon() { return icon; }
	SkillBaseType GetSkillType() { return skillBaseType; }
	string GetSkillName() { return skillName; }

protected:
	// 선행스킬 이름
	vector<string> prevSkills;

	// 스킬의 이름
	string skillName;

	// 해당 스킬을 가지는 플레이어에 대한 정보
	class CH_Base_ver2* owner;

	Quad* icon;

	SkillBaseType skillBaseType;
};