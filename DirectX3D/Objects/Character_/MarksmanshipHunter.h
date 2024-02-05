#pragma once
class MarksmanshipHunter : public CH_Base
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
	MarksmanshipHunter(CreatureType type);
	~MarksmanshipHunter();

	virtual void Update() override;
	virtual void Render() override;

	// �÷��̾�� ������Ʈ
	virtual void PlayerUpdate() override;
	// NPC�� ������Ʈ
	virtual void AIUpdate() override;

	void Moving();
	void Jump();
	void Attack();
	void Casting();

	virtual void OnHit(Collider* collider) override;

	void EndATK();
	void EndJUMP();
	void EndHit();
	void EndDie();
	void EndCasting();

private:
	State curState = IDLE1;
};