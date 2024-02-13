﻿#pragma once
class ProtectionWarrior_in : public CH_Base_ver2
{
public:
	enum State
	{
		IDLE1,
		ATTACK1,
		WALK_F, WALK_B, WALK_L, WALK_R,
		DIE, HIT, JUMP,
		SKILL1,
	};

public:

    ProtectionWarrior_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
    ~ProtectionWarrior_in();

	virtual void Update() override;
	virtual void Render() override;

	void SetState(State state);

private:
	// 플레이어용 업데이트
	virtual void PlayerUpdate() override;
	// NPC용 업데이트
	virtual void AIUpdate() override;
	// 충돌 판정 함수
	virtual void OnHit(float damage) override;

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

	// 상태 변경용 함수
	

	// 이벤트 함수
private:
	void EndATK();
	void EndHit();
	void EndDie();
	void EndCasting();

private:
	State curState = IDLE1;
};