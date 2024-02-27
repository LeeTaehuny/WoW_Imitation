#pragma once
class FireMage_in : public CH_Base_ver2
{
public:

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
	virtual void GUIRender();

public:
	void SetDoubleDamage(bool value) { isDouble = value; }
	bool GetDoubleDamage() { return isDouble; }

	// 상태 변경용 함수
	void SetState(State state);
	State GetState() { return curState; }

	virtual void EquipWeapon(class Weapon* weapon) override;

private:
	// 플레이어용 업데이트
	virtual void PlayerUpdate() override;
	// NPC용 업데이트
	virtual void AIUpdate() override;
	// 충돌 판정 함수
	virtual void OnHit(float damage, bool motion = false) override;

	virtual void AI_animation_Moving() override;

// 컨트롤 관련 함수
private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	void Control();
	void Moving();
	void Jump();
	void Attack();
	void ai_attack();
	//void Casting();

// 이벤트 함수
private:
	void EndATK();
	void EndHit();
	void EndDie();
	//void EndCasting();

private:
	// 버프용 변수 (데미지 2배)
	bool isDouble = false;

	State curState = IDLE1;
};

