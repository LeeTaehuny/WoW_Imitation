#pragma once
class CH_Base : public ModelAnimator
{
public:
	CH_Base(string name, int myNober) : ModelAnimator(name)
	{ this->myNober = myNober; }
	virtual ~CH_Base() = default;

	// 플레이어용 업데이트
	void PlayerUpdate();
	// NPC용 업데이트
	void AIUpdate();
	// 모션 설정
	void SetState(int state);
	void Render();

	Collider* GetCollider() { return collider; }


public: // 가상 함수

	// 키보드 조작용 움직임
	virtual void Moving() = 0;
	// 키보드 조작용 움직임
	virtual void Jump() = 0;
	// 공격 함수
	virtual void Attack() = 0;
	// 캐스팅 함수
	virtual void Casting() = 0;

	// 다른 콜라이더와 충돌했을 때
	virtual void OnHit(Collider* collider) = 0;

	bool isCasting = false;
	int myNober = 0;
protected:
	int INTstate = 0;
	Vector3 velocity;
	bool isJump = false;

	Collider* collider;


protected: // 스탯 관련

	float Max_hp = 0;
	float cur_hp = Max_hp;
};