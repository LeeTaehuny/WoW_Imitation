#pragma once

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

// 캐릭터의 스탯 정보
struct Status
{
	float maxHp;	// 최대 체력
	float hp;		// 체력
	int maxMp;		// 최대 마나
	int mp;			// 마나
	int defence;	// 방어력
	float damage;	// 데미지
};

class CH_Base_ver2 : public Transform
{
public:
	CH_Base_ver2(CreatureType creatureType, ProfessionType professionType);
	virtual ~CH_Base_ver2();

	virtual void Update();
	virtual void Render();
	void UIRender();
	virtual void GUIRender() {};

	// 캐릭터가 플레이어일 경우 업데이트하기 위한 함수
	virtual void PlayerUpdate() = 0;
	// 캐릭터가 NPC일 경우 업에이트하기 위한 함수
	virtual void AIUpdate() = 0;
	// 데미지를 받기 위한 함수
	virtual void OnHit(float damage, bool motion = false) = 0;

	// 플레이어가 스킬을 학습하기 위한 함수
	bool LearnSkill(class SkillBase* skill);

	// 체력 & 마나 회복 함수
	void AddHp(int amount);
	void AddMp(int amount);

	// NPC의 이동 함수
	virtual void AI_animation_Moving() = 0;

	// 무기 장착 함수
	virtual void EquipWeapon(class Weapon* weapon) = 0;

	// 무기 초기화
	void ClearWeapon();

// Getter & Setter
public:
	// 인벤토리 정보를 얻기 위한 겟터 함수
	class Inventory* GetInventory() { return inventory; }
	// 캐릭터의 콜라이더를 얻기 위한 겟터 함수
	Collider* GetCollider() { return myCollider; }
	// 플레이어일 경우 NPC들의 활동범위
	// NPC일 경우 적대 몬스터를 감지해냄
	Collider* GetRange() { return range; }

	// NPC의 경우 플레이어의 정보를 설정함
	void SetPlayer(CH_Base_ver2* myPlayer) { this->myPlayer = myPlayer; };

	// 인스턴싱 겟터
	ModelAnimatorInstancing* GetInstancing() { return instancing; }
	// 인스턴싱의 인덱스 정보 겟터
	UINT GetIndex() { return index; }

	// 높이 설정
	void SetHeight(float value) { curheight = value; }
	// 현재 높이 겟터 함수
	float& GettHeight() { return curheight; }

	// 스탯을 설정하기 위한 함수
	void SetStat(Status stat) { this->stat = stat; }
	// 스탯정보를 받아오기 위한 겟터 함수
	Status& GetStat() { return stat; }

	// 스킬들의 벡터 정보를 얻기 위한 겟터 함수
	vector<class SkillBase*>& GetSkillList() { return skillList; }

	// 무기의 정보를 얻기 위한 겟터 함수
	class Weapon* GetWeapon() { return weapon; }

	// 타겟 몬스터를 설정하기 위한 셋터 함수
	void SetSelectTarget(class MonsterBase* monster) { monsterSelectData = monster; }
	// NPC의 경우 몬스터들을 공격함
	void SetAttackOrder() { this->atkTarget = !this->atkTarget; }

	// Member Variable
	// 직업
	ProfessionType GetProfessionType() { return professionType; }

	// target
	class MonsterBase* GetTargetMonster() { return targetMonster; }
	// 캐릭터의 정보를 얻기 위한 겟터 함수 (회복스킬을 위한 함수)
	CH_Base_ver2* GetTargetCharacter() { return targetCharacter; }

	// 퀵슬롯
	class QuickSlot* GetQuickSlot() { return quickSlot; }

	// 플레이어 UI
	class PlayerUI_Bar* GetPlayerUI() { return playerUI; }

	// 플레이어인지 NPC인지 정보를 얻기 위한 겟터
	CreatureType GetcreatureType() { return creatureType; }

// Member Variable
protected:
	CreatureType creatureType;
	ProfessionType professionType;

	// 내 콜라이더 변수
	Collider* myCollider;

	class Inventory* inventory;
	class StatusUI* statusUI;
	class QuickSlot* quickSlot;

	class MonsterBase* targetMonster;
	CH_Base_ver2* targetCharacter;

	// 스킬
	vector<class SkillBase*> skillList;
	map<string, int> prevSkills;

protected:
	// 인스턴싱 정보들을 모아놓은 곳
	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;
	UINT index;
	UINT mainHandBoneIndex;

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
	// 스테이터스
	Status stat;
	// UI
	class PlayerUI_Bar* playerUI;
	class MonsterUI_Bar* monsterUI;
	
	class Weapon* weapon;


	Transform* mainHand;

protected: // 평타 및 스킬을 사용할때 참고하기 위한 변수들

	// 현재 선택된 몬스터의 정보를 받기 위한 변수
	class MonsterBase* monsterSelectData; 
	class CH_Base_ver2* characterSelectData;


protected: // NPC가 사용할 변수들의 목록

	// 플레이어일 경우 NPC들의 활동범위
	// NPC일 경우 적대 몬스터를 감지해냄
	Collider* range;

	// NPC에게 플레이어의 정보를 저장하기 위한 변수
	CH_Base_ver2* myPlayer;

	// NPC가 랜덤행동을 하기 위한 타이머의 최대 시간
	float MAX_randomHangdong = 5;
	// 시작하자마자 바로 실행시키기 위한 변수
	float randomHangdong = -1;
	// 플레이어의 주변을 떠돌때 방향을 정하기 위한 변수
	Vector3 randomVelocity;

	// NPC에게 적을 공격할지 안할지 명령을 내리는 변수
	bool atkTarget = false;
	// 행동 틱 1초 단위
	float Max_ActionTickTime = 1.0f;
	float ActionTickTime = Max_ActionTickTime;
};