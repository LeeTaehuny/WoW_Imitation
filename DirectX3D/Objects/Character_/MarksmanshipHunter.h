#pragma once
class MarksmanshipHunter : public CH_Base
{
private:
	enum State
	{
		IDLE1,
		ATTACK1,
		WALK_F, WALK_B, WALK_L, WALK_R,
		DIE, HIT, JUMP,
		SKILL1, SKILL2
	};

public:
	MarksmanshipHunter(CreatureType type);
	~MarksmanshipHunter();

	virtual void Update() override;
	virtual void Render() override;

private:
	// 플레이어용 업데이트
	virtual void PlayerUpdate() override;
	// NPC용 업데이트
	virtual void AIUpdate() override;
	// 충돌 판정 함수
	virtual void OnHit(Collider* collider) override;

	// 컨트롤 관련 함수
private:
	void Control();
	void Moving();
	void Jump();
	void Attack();
	//void Casting();

	// 상태 변경용 함수
	void SetState(State state);

	// 이벤트 함수
private:
	void EndATK();
	void EndHit();
	void EndDie();
	//void EndCasting();

private:
	State curState = IDLE1;

};