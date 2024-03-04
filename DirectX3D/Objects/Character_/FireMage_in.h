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

	// 무기 할당을 위한 함수
	virtual void EquipWeapon(class Weapon* weapon) override;

private:
	// 플레이어용 업데이트
	virtual void PlayerUpdate() override;
	// NPC용 업데이트
	virtual void AIUpdate() override;
	// 충돌 판정 함수
	virtual void OnHit(float damage, bool motion = false) override;

	// NPC가 움직이기 위한 함수
	virtual void AI_animation_Moving() override;


private: // 컨트롤 관련 함수

	// 애니메이션 이벤트를 할당하기 위한 함수
	void SetEvent(int clip, Event event, float timeRatio);
	// 애니메이션 인스턴싱 함수
	void ExecuteEvent();

	// 플레이어 컨트롤을 종합하는 함수
	void Control();
	// 플레이어의 움직임을 담당하는 함수
	void Moving();
	// 플레이어의 점프를 담당하는 함수
	void Jump();
	// 플레이어의 공격을 담당하는 함수
	void Attack();

	// NPC의 공격을 담당하는 함수
	void ai_attack();

private: // 이벤트 함수

	// 공격 애니메이션이 종료되었을때 실행되는 함수
	void EndATK();
	// 히트 애니메이션이 종료되었을때 실행되는 함수
	void EndHit();
	// 죽음 애니메이션이 종료되었을때 실행되는 함수
	void EndDie();

private:
	// 버프용 변수 (데미지 2배)
	bool isDouble = false;

	State curState = IDLE1;

private:
	// 공격 음원 재생 여부
	bool isPlayAttackSound = false;
	bool isRun = false;
	float attackSoundDelay = 0.0f;

	bool one_die = false;
};

