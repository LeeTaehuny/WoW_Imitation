#pragma once
class ArmsWarrior_in : public CH_Base_ver2
{
public:

	enum State
	{
		IDLE1, IDLE2,
		ATTACK1, ATTACK2,
		WALK_F, WALK_B, WALK_L, WALK_R,
		DIE, HIT, JUMP,
	};

public:

	ArmsWarrior_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~ArmsWarrior_in();

	virtual void Update() override;
	virtual void Render() override;

public:
	void SetBuffDefence(bool value) { isDefence = value; }
	void SetBuffLifeDrain(bool value) { isLifeDrain = value; }
	bool GetBuffLifeDrain() { return isLifeDrain; }

	virtual void EquipWeapon(class Weapon* weapon) override;
	void AddHp(float value);

	// ���� ����� �Լ�
	void SetState(State state);
	State GetState() { return curState; }

private:
	// �÷��̾�� ������Ʈ
	virtual void PlayerUpdate() override;
	// NPC�� ������Ʈ
	virtual void AIUpdate() override;
	// �浹 ���� �Լ�
	virtual void OnHit(Collider* collider) override;

	virtual void AI_animation_Moving() override;

// ��Ʈ�� ���� �Լ�
private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	void Control();
	void Moving();
	void Jump();
	void Attack();
	//void Casting();

// �̺�Ʈ �Լ�
private:
	void EndATK();
	void EndHit();
	void EndDie();
	//void EndCasting();

private:
	// ������ ���� (���� 1.3��)
	bool isDefence = false;
	// ������ ���� (���� ���)
	bool isLifeDrain = false;

	State curState = IDLE1;
};