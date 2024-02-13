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

	// 상태 변경용 함수
	void SetState(State state);
	State GetState() { return curState; }

private:
	// 플레이어용 업데이트
	virtual void PlayerUpdate() override;
	// NPC용 업데이트
	virtual void AIUpdate() override;
	// 충돌 판정 함수
	virtual void OnHit(Collider* collider) override;

	virtual void AI_animation_Moving() override;

// 컨트롤 관련 함수
private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	void Control();
	void Moving();
	void Jump();
	void Attack();
	//void Casting();

// 이벤트 함수
private:
	void EndATK();
	void EndHit();
	void EndDie();
	//void EndCasting();

private:
	// 버프용 변수 (방어력 1.3배)
	bool isDefence = false;
	// 버프용 변수 (피해 흡수)
	bool isLifeDrain = false;

	State curState = IDLE1;
};