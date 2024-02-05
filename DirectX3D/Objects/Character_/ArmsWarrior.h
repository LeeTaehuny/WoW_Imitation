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
	ArmsWarrior();
	~ArmsWarrior();

	virtual void Moving() override;
	virtual void Jump() override;
	virtual void Attack() override;
	virtual void Casting() override;

	virtual void OnHit(Collider* collider) override;

	void EndATK();
	void EndJUMP();
	void EndHit();
	void EndDie();
	void EndCasting();

private:
	State curState = IDLE1;
	
};