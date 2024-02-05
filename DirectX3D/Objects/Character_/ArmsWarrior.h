#pragma once
class ArmsWarrior : public CH_Base
{
private:
	enum State
	{
		IDLE1, IDLE2,
		ATTACK1, ATTACK2,
		WALK_F, WALK_B, WALK_L, WALK_R,
		DIE, HIT, JUMP,
	};

public:
	ArmsWarrior(CreatureType type);
	~ArmsWarrior();

	virtual void Update() override;
	virtual void Render() override;


	// 플레이어용 업데이트
	virtual void PlayerUpdate() override;
	// NPC용 업데이트
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