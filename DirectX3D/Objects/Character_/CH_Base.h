#pragma once
class CH_Base : public ModelAnimator
{
public:
	CH_Base(string name, int myNober) : ModelAnimator(name)
	{ this->myNober = myNober; }
	virtual ~CH_Base() = default;

	// �÷��̾�� ������Ʈ
	void PlayerUpdate();
	// NPC�� ������Ʈ
	void AIUpdate();
	// ��� ����
	void SetState(int state);
	void Render();

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

	bool isCasting = false;
	int myNober = 0;
protected:
	int INTstate = 0;
	Vector3 velocity;
	bool isJump = false;

	Collider* collider;


protected: // ���� ����

	float Max_hp = 0;
	float cur_hp = Max_hp;
};