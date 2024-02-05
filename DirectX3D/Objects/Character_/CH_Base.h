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

class CH_Base : public ModelAnimator
{
public:
	CH_Base(string name, CreatureType creatureType, ProfessionType professionType);
	virtual ~CH_Base();

	virtual void Update();
	virtual void Render();
	void UIRender();

public:
	// �÷��̾�� ������Ʈ
	virtual void PlayerUpdate() = 0;
	// NPC�� ������Ʈ
	virtual void AIUpdate() = 0;
	// �ٸ� �ݶ��̴��� �浹���� ��
	virtual void OnHit(Collider* collider) = 0;

// Getter & Setter
public:
	class Inventory* GetInventory() { return inventory; }
	Collider* GetCollider() { return collider; }

protected:
	void SetState(int state);

// Member Variable
protected:
	CreatureType creatureType;
	ProfessionType professionType;

	int INTstate = 0;
	Vector3 velocity;
	bool isJump = false;
	bool isCasting = false;
	Collider* collider;

	class Inventory* inventory;

	float Max_hp = 0;
	float cur_hp = Max_hp;
};