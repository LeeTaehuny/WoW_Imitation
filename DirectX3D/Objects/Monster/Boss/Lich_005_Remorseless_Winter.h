#pragma once
class Lich_005_Remorseless_Winter : public Lich_000_Base
{
public:
	Lich_005_Remorseless_Winter(Boss_LichKing* lich);
	~Lich_005_Remorseless_Winter();

	virtual void Update() override;
	virtual void Render() override;
	// 스킬 사용에 쓰기 위한 함수
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

	// 해당 스킬이 종료되었는지를 알기 위한 함수
	bool GetSkillEnd() { return skillend; }
	// 스킬종료 변수의 값을 반전시키기 위한 함수
	void ChangeSkillEnd() { skillend = !skillend; }

private:
	ParticleSystem* particle;
	Collider* hitCollider;

	// 0.5초마다 데미지를 주게하기 위한 변수
	float Max_tickTime = 0.5f;
	float tickTime = Max_tickTime;

	// 스킬이 종료되었는지를 판별하기 위한 변수
	bool skillend = false;

	// 60초만 작동하도록 하게하기 위한 변수
	float Max_runTime = 10.0f;
	float runTime = Max_runTime;
};