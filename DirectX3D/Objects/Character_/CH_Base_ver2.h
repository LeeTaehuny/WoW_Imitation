#pragma once

enum class CreatureType
{
	Player,
	NonPlayer,
};

enum class ProfessionType
{
	ArmsWarrior,		// ����[����]
	ProtectionWarrior,  // �����[��ȣ]
	MarksmanshipHunter, // ��ɲ�[���]
	FireMage,			// ������[ȭ��]
	HolyPriest,			// ����[�ż�]
};

// ������ �����ϱ� ���� ����ü
struct Status
{
	float maxHp;	// �ִ� ü��
	float hp;		// ���� ü��
	int maxMp;
	int mp;			// ����
	int defence;	// ����
	float damage;	// ���ݷ�
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

	// �÷��̾�� ������Ʈ
	virtual void PlayerUpdate() = 0;
	// NPC�� ������Ʈ
	virtual void AIUpdate() = 0;
	// �ٸ� �ݶ��̴��� �浹���� ��
	virtual void OnHit(float damage) = 0;

	bool LearnSkill(class SkillBase* skill);

	// 체력 & 마나 회복 함수
	void AddHp(int amount);
	void AddMp(int amount);

	virtual void AI_animation_Moving() = 0;

	virtual void EquipWeapon(class Weapon* weapon) = 0;

	void ClearWeapon();

// Getter & Setter
public:
	class Inventory* GetInventory() { return inventory; }
	Collider* GetCollider() { return myCollider; }
	Collider* GetRange() { return range; }

	void SetPlayer(CH_Base_ver2* myPlayer) { this->myPlayer = myPlayer; };

	ModelAnimatorInstancing* GetInstancing() { return instancing; }
	UINT GetIndex() { return index; }

	void SetHeight(float value) { curheight = value; }
	float& GettHeight() { return curheight; }

	// ����
	void SetStat(Status stat) { this->stat = stat; }
	Status& GetStat() { return stat; }

	// ��ų
	vector<class SkillBase*>& GetSkillList() { return skillList; }

	// 무기
	class Weapon* GetWeapon() { return weapon; }

	void SetSelectTarget(class MonsterBase* monster) { monsterSelectData = monster; }
	void SetAttackOrder() { this->atkTarget = !this->atkTarget; }

	// Member Variable
	// 직업
	ProfessionType GetProfessionType() { return professionType; }

	// target
	class MonsterBase* GetTargetMonster() { return targetMonster; }
	CH_Base_ver2* GetTargetCharacter() { return targetCharacter; }

	// 퀵슬롯
	class QuickSlot* GetQuickSlot() { return quickSlot; }

	// 플레이어 UI
	class PlayerUI_Bar* GetPlayerUI() { return playerUI; }

// Member Variable
protected:
	CreatureType creatureType;
	ProfessionType professionType;

	// �÷��̾� ������ �浹 �ݶ��̴�
	Collider* myCollider;

	class Inventory* inventory;
	class StatusUI* statusUI;
	class QuickSlot* quickSlot;

	class MonsterBase* targetMonster;
	CH_Base_ver2* targetCharacter;

	// 스킬
	vector<class SkillBase*> skillList;
	map<string, int> prevSkills;

	// �ν��Ͻ̿� �ʿ��� ������
protected:
	// �ν��Ͻ� ����
	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;
	UINT index; // ���� ������� �ִϸ��̼�
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
	class MonsterBase* monsterSelectData; // 현재 선택된 몬스터의 정보를 받기 위한 변수
	class CH_Base_ver2* characterSelectData;


protected: // NPC ĳ���͸� �����ϱ� ���� ���� �� �Լ�

	// �÷��̾�� ����ȴٸ� NPC���� Ȱ�� ����
	// NPC�� ������ �ȵǸ� ��Ÿ ��Ÿ��� �ȴ�.
	Collider* range;

	// �÷��̾��� ������ �޾ƿ��� ���� ����
	CH_Base_ver2* myPlayer;

	// �÷��̾��� �ֺ��� NPC�� ���� ��� �������� �����̰� �ϱ� ���� ������
	float MAX_randomHangdong = 5;
	float randomHangdong = -1; // -1�� �ִ� ������ ù ������Ʈ ������ �������� �۵���Ű�� ����
	Vector3 randomVelocity;

	// 공격할 타겟이 있는지를 구분하기 위한 변수
	bool atkTarget = false;
	// 행동 틱 1초 단위
	float Max_ActionTickTime = 1.0f;
	float ActionTickTime = Max_ActionTickTime;
};