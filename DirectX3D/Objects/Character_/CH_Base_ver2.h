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

	// �÷��̾�� ������Ʈ
	virtual void PlayerUpdate() = 0;
	// NPC�� ������Ʈ
	virtual void AIUpdate() = 0;
	// �ٸ� �ݶ��̴��� �浹���� ��
	virtual void OnHit(Collider* collider) = 0;

	virtual void LearnSkill(class SkillBase* skill) {};

	virtual void AI_animation_Moving() = 0;

	virtual void EquipWeapon(class Weapon* weapon) = 0;

// Getter & Setter
public:
	class Inventory* GetInventory() { return inventory; }
	Collider* GetCollider() { return myCollider; }
	Collider* GetRange() { return range; }

	void SetPlayer(CH_Base_ver2* myPlayer) { this->myPlayer = myPlayer; };

	ModelAnimatorInstancing* GetInstancing() { return instancing; }
	UINT GetIndex() { return index; }

	// ����
	void SetStat(Status stat) { this->stat = stat; }
	Status& GetStat() { return stat; }

	// ��ų
	vector<class SkillBase*>& GetSkillList() { return skillList; }

	// 무기
	class Weapon* GetWeapon() { return weapon; }

// Member Variable
protected:
	CreatureType creatureType;
	ProfessionType professionType;

	// �÷��̾� ������ �浹 �ݶ��̴�
	Collider* myCollider;

	class Inventory* inventory;

	// ��ų
	vector<class SkillBase*> skillList;

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
	Status stat;
	class Weapon* weapon;

	Transform* mainHand;

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
};