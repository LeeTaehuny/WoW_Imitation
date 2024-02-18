#pragma once
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
	void ai_attack();
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
};