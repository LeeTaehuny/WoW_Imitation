#pragma once
class MarksmanshipHunter_in : public CH_Base_ver2
{
private:

	enum State
	{
		IDLE1,
		ATTACK1,
		WALK_F, WALK_B, WALK_L, WALK_R,
		DIE, HIT, JUMP,
		SKILL1, SKILL2
	};

public:

	MarksmanshipHunter_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~MarksmanshipHunter_in();

	virtual void Update() override;
	virtual void Render() override;

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
	State curState = IDLE1;
};