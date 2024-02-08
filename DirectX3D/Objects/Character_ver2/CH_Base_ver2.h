#pragma once

//enum class CreatureType
//{
//	Player,
//	NonPlayer,
//};
//
//enum class ProfessionType
//{
//	ArmsWarrior,		// 전사[무기]
//	ProtectionWarrior,  // 성기사[보호]
//	MarksmanshipHunter, // 사냥꾼[사격]
//	FireMage,			// 마법사[화염]
//	HolyPriest,			// 사제[신성]
//};

class CH_Base_ver2 : public Transform
{
public:
	CH_Base_ver2(CreatureType creatureType, ProfessionType professionType);
	virtual ~CH_Base_ver2();

	virtual void Update();
	virtual void Render();
	void UIRender();

	// 플레이어용 업데이트
	virtual void PlayerUpdate() = 0;
	// NPC용 업데이트
	virtual void AIUpdate() = 0;
	// 다른 콜라이더와 충돌했을 때
	virtual void OnHit(Collider* collider) = 0;

	virtual void LearnSkill(class SkillBase* skill) {};

	virtual void AI_animation_Moving() = 0;

	// Getter & Setter
public:
	class Inventory* GetInventory() { return inventory; }
	Collider* GetCollider() { return myCollider; }
	Collider* GetRange() { return range; }

	void SetPlayer(CH_Base_ver2* myPlayer) { this->myPlayer = myPlayer; };

	// Member Variable
protected:
	CreatureType creatureType;
	ProfessionType professionType;

	// 플레이어 본인의 충돌 콜라이더
	Collider* myCollider;

	class Inventory* inventory;

	// 스킬
	vector<class SkillBase> skillList;

protected: // 인스턴싱에 필요한 정보들
	// 인스턴싱 정보
	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;
	UINT index; // 현재 재생중인 애니메이션

	vector<map<float, Event>> totalEvents;
	vector<map<float, Event>::iterator> eventIters;

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

protected: // NPC 캐릭터를 구현하기 위한 변수 및 함수

	// 플레이어로 선언된다면 NPC들의 활동 범위
	// NPC로 선언이 된되면 평타 사거리가 된다.
	Collider* range;

	// 플레이어의 정보를 받아오기 위한 정보
	CH_Base_ver2* myPlayer;

	// 플레이어의 주변에 NPC가 있을 경우 랜덤으로 움직이게 하기 위한 변수들
	float MAX_randomHangdong = 5;
	float randomHangdong = -1; // -1을 주는 이유는 첫 업데이트 문에서 이프문을 작동시키기 위해
	Vector3 randomVelocity;
};