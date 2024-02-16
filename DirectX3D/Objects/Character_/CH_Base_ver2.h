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
	virtual void OnHit(float damage) = 0;

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

	vector<bool> GetAttackSignal() { return attackSignal; }
	// 캐릭터의 공격 혹은 스킬에 신호를 주기위한 함수
	// 일반공격 = 0
	// 무기 전사 : 4개
	// 보호 팔라딘 : 3개
	// 화염 마법사 : 6개
	// 저격 사냥꾼 : 6개
	// 신성 사제 : 6개
	void SetAttackSignal(int value) { attackSignal[value] = !attackSignal[value]; }
	void SetSelectTarget(class MonsterBase* monster) { monsterSelectData = monster; }
	void SetAttackOrder() { this->atkTarget = !this->atkTarget; }

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

protected: // 평타 및 스킬을 사용할때 참고하기 위한 변수들
	vector<bool> attackSignal; // 어떤 공격을 할지에 대한 판별용 벡터 변수
	class MonsterBase* monsterSelectData; // 현재 선택된 몬스터의 정보를 받기 위한 변수


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