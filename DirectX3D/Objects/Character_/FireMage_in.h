#pragma once
class FireMage_in : public CH_Base_ver2
{
private:

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

public:
	void SetDoubleDamage(bool value) { isDouble = value; }

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

	// ���� ����� �Լ�
	void SetState(State state);

// �̺�Ʈ �Լ�
private:
	void EndATK();
	void EndHit();
	void EndDie();
	//void EndCasting();

private:
	// ������ ���� (������ 2��)
	bool isDouble = false;

	State curState = IDLE1;
};

