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
	virtual void GUIRender();

public:
	virtual void EquipWeapon(class Weapon* weapon) override;
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
	// 캐스팅 애니메이션이 종료되었을때 실행되는 함수
	void EndCasting();

private:
	State curState = IDLE1;

	// 팔라딘의 실제 공격 사거리
	Collider* attackRange;

	// 받아온 몬스터의 콜라이더 정보를 저장하기 위한 변수
	Collider* saveMonsterCollider;

	int impact = 0;
	bool atkGannnnn = false;

	bool skill001;
	bool skill002;
	bool skill009;

	int imsiSkillStart = 0;

	bool one_atk_sound = false;
	bool one_atk_sound02 = false;
	float Max_one_atk_time = 0.55f;
	float one_atk_time = Max_one_atk_time;

private:
	Transform* sub;
	class Weapon* shield;
	bool one_die = false;
};