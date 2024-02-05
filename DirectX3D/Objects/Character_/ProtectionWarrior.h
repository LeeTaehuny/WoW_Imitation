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
	ProtectionWarrior(CreatureType type);
	~ProtectionWarrior();

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
	void EndIDLE();
	void EndHit();
	void EndDie();
	void EndCasting();

public:
	State curState = IDLE1;
	

};