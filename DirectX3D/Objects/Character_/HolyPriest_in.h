﻿#pragma once
class HolyPriest_in : public CH_Base_ver2
{
public:

	// 사제 전용
	enum State
	{
		IDLE1, IDLE2, IDLE3,
		ATTACK1, ATTACK2,
		WALK_F, WALK_B, WALK_L, WALK_R,
		DIE, HIT, JUMP,
	};

public:

	HolyPriest_in(CreatureType type, Transform* transform, ModelAnimatorInstancing* instancing, UINT index);
	~HolyPriest_in();

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender();

public:
	// 무기 장착 함수
	virtual void EquipWeapon(class Weapon* weapon) override;
	// 애니메이션을 변경하기 위한 변수
	void SetState(State state);

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

	// 애니메이션 이벤트 설정용 함수
	void SetEvent(int clip, Event event, float timeRatio);
	// 애니메이션 인스턴싱용 함수
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
	State curState = IDLE1;
	float target_Proportion = 0;

	float heal = false; // 회복할 아군이 있는지를 판별하기 위한 변수
	float atk = false; // 공격할 적이 있는지를 판별하기 위한 변수

	Collider* skillRange;
	bool use002skill = false; // 002스킬을 사용할지 안할지를 판별하는 변수
	bool use008skill = false; // 008 스킬을 사용중인지 아닌지를 판별하는 함수
	float Max_pressSkill = 5.0f;
	float pressSkill = Max_pressSkill;
	bool isRun008skill;

private:

	bool one_atk_sound = false;
	bool one_atk_sound02 = false;
	float Max_one_atk_time = 0.4f;
	float one_atk_time = Max_one_atk_time;

	bool one_die = false;
};

