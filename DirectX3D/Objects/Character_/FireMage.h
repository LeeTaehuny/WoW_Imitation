#pragma once
class FireMage : public CH_Base
{
	enum State
	{
		IDLE1, IDLE2,
		ATTACK1, ATTACK2, ATTACK3,
		WALK_F, WALK_B, WALK_L, WALK_R,
		DIE1, DIE2, HIT1, HIT2, JUMP,
	};

public:
	FireMage(int myNober);
	~FireMage();

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