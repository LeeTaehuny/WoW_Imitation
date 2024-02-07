#pragma once
#include "Objects/Skills/Base/SkillBase.h"

enum class CreatureType
{
	Player,
	NonPlayer,
};

enum class ProfessionType
{
	ArmsWarrior,		// 전사[무기]
	ProtectionWarrior,  // 성기사[보호]
	MarksmanshipHunter, // 사냥꾼[사격]
	FireMage,			// 마법사[화염]
	HolyPriest,			// 사제[신성]
};

class CH_Base : public ModelAnimator
{
public:
	CH_Base(string name, CreatureType creatureType, ProfessionType professionType);
	virtual ~CH_Base();

	virtual void Update();
	virtual void Render();
	void UIRender();

public:
	// 플레이어용 업데이트
	virtual void PlayerUpdate() = 0;
	// NPC용 업데이트
	virtual void AIUpdate() = 0;
	// 다른 콜라이더와 충돌했을 때
	virtual void OnHit(Collider* collider) = 0;

	virtual void LearnSkill(class SkillBase* skill) {};

// Getter & Setter
public:
	class Inventory* GetInventory() { return inventory; }
	Collider* GetCollider() { return collider; }

// Member Variable
protected:
	CreatureType creatureType;
	ProfessionType professionType;

	Collider* collider;

	class Inventory* inventory;

	// 스킬
	vector<class SkillBase> skillList;

protected:
	Vector3 velocity;
	bool isCasting = false;
	float moveSpeed = 10.0f;
	float deceleration = 10;
	float turnSpeed = 2;

	float jumpVelocity = 0;
	float jumpForce = 0.15f;
	float gravityMult = 0.5f;
	bool isJump = false;

	float curheight = 0.0f;

protected:
	// 임시 코드.
	float Max_hp = 0;
	float cur_hp = Max_hp;
};