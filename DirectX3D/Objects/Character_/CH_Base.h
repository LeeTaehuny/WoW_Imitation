#pragma once
class CH_Base : public ModelAnimator
{
public:
	CH_Base(string name);
	virtual ~CH_Base() = default;

	// �÷��̾�� ������Ʈ
	void PlayerUpdate();
	// NPC�� ������Ʈ
	void AIUpdate();
	// ��� ����
	void SetState(int state);
	void Render();
	void UIRender();

	Collider* GetCollider() { return collider; }


public: // ���� �Լ�

	// Ű���� ���ۿ� ������
	virtual void Moving() = 0;
	// Ű���� ���ۿ� ������
	virtual void Jump() = 0;
	// ���� �Լ�
	virtual void Attack() = 0;
	// ĳ���� �Լ�
	virtual void Casting() = 0;

	// �ٸ� �ݶ��̴��� �浹���� ��
	virtual void OnHit(Collider* collider) = 0;

// Getter & Setter
public:
	class Inventory* GetInventory() { return inventory; }

protected:
	int INTstate = 0;
	Vector3 velocity;
	bool isJump = false;
	bool isCasting = false;
	Collider* collider;


protected: // ���� ����

	float Max_hp = 0;
	float cur_hp = Max_hp;

// �κ��丮
protected:
	class Inventory* inventory;
};