#pragma once
class ProtectionWarrior : public CH_Base
{
private:

	enum State
	{
		IDLE1, IDLE2, IDLE3,
		ATTACK1,
		WALK_F, WALK_B, WALK_L, WALK_R,
		DIE, HIT, JUMP,
		SKILL1,
	};

public:
	ProtectionWarrior(int myNober);
	~ProtectionWarrior();

	virtual void Moving() override;
	virtual void Jump() override;
	virtual void Attack() override;
	virtual void Casting() override;

	virtual void OnHit(Collider* collider) override;

	void EndATK();
	void EndJUMP();
	void EndIDLE();
	void EndHit();
	void EndDie();
	void EndCasting();

public:
	State curState = IDLE1;
	

};