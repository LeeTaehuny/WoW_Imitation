#pragma once
class FireMage_in : public CH_Base_ver2
{
public:

	enum State
	{
		IDLE1, IDLE2,
		ATTACK1, ATTACK2, ATTACK3,
		WALK_F, WALK_B, WALK_L, WALK_R,
		DIE, HIT, JUMP,
	};

public:

	FireMage_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~FireMage_in();

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender();

public:
	void SetDoubleDamage(bool value) { isDouble = value; }
	bool GetDoubleDamage() { return isDouble; }

	// ���� ����� �Լ�
	void SetState(State state);
	State GetState() { return curState; }

	// ���� �Ҵ��� ���� �Լ�
	virtual void EquipWeapon(class Weapon* weapon) override;

private:
	// �÷��̾�� ������Ʈ
	virtual void PlayerUpdate() override;
	// NPC�� ������Ʈ
	virtual void AIUpdate() override;
	// �浹 ���� �Լ�
	virtual void OnHit(float damage, bool motion = false) override;

	// NPC�� �����̱� ���� �Լ�
	virtual void AI_animation_Moving() override;


private: // ��Ʈ�� ���� �Լ�

	// �ִϸ��̼� �̺�Ʈ�� �Ҵ��ϱ� ���� �Լ�
	void SetEvent(int clip, Event event, float timeRatio);
	// �ִϸ��̼� �ν��Ͻ� �Լ�
	void ExecuteEvent();

	// �÷��̾� ��Ʈ���� �����ϴ� �Լ�
	void Control();
	// �÷��̾��� �������� ����ϴ� �Լ�
	void Moving();
	// �÷��̾��� ������ ����ϴ� �Լ�
	void Jump();
	// �÷��̾��� ������ ����ϴ� �Լ�
	void Attack();

	// NPC�� ������ ����ϴ� �Լ�
	void ai_attack();

private: // �̺�Ʈ �Լ�

	// ���� �ִϸ��̼��� ����Ǿ����� ����Ǵ� �Լ�
	void EndATK();
	// ��Ʈ �ִϸ��̼��� ����Ǿ����� ����Ǵ� �Լ�
	void EndHit();
	// ���� �ִϸ��̼��� ����Ǿ����� ����Ǵ� �Լ�
	void EndDie();

private:
	// ������ ���� (������ 2��)
	bool isDouble = false;

	State curState = IDLE1;

private:
	// ���� ���� ��� ����
	bool isPlayAttackSound = false;
	bool isRun = false;
	float attackSoundDelay = 0.0f;

	bool one_die = false;
};

