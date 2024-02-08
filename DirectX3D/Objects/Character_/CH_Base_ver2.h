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

	// �÷��̾� ������ �浹 �ݶ��̴�
	Collider* myCollider;

	class Inventory* inventory;

	// ��ų
	vector<class SkillBase> skillList;

protected: // �ν��Ͻ̿� �ʿ��� ������
	// �ν��Ͻ� ����
	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;
	UINT index; // ���� ������� �ִϸ��̼�

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
	// �ӽ� �ڵ�.
	float Max_hp = 0;
	float cur_hp = Max_hp;

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