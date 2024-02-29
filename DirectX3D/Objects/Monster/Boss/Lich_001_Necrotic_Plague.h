#pragma once
class Lich_001_Necrotic_Plague : public Lich_000_Base
{
public:
	Lich_001_Necrotic_Plague(Boss_LichKing* lich);
	~Lich_001_Necrotic_Plague();

	virtual void Update() override;
	virtual void Render() override;
	// 스킬 사용에 쓰기 위한 함수
	virtual void UseSkill(CH_Base_ver2* chbase) override;
	
private:
	ParticleSystem* particle;
	CH_Base_ver2* characterData;
	Collider* Yad;

private:
	// 한 번만 발동시키게 하기 위한 변수
	int isOne = 0;
	// 틱 데미지를 몇 번 주었는지 판별하기 위한 변수 : 값이 3이 되면 정지
	int tickDamageCount;

	// 마지막 공격 혹은 첫 스킬 발동시 해당 타겟의 체력을 
	// 저장하여 다음 연산에 사용하기 위한 변수
	float charcter_HP_LastData;
	// 최대 체력 30%의 값을 저장하기 위한 변수
	float charcter_HP_ratio;


	// 5초마다 틱 데미지를 주기 위한 변수
	float Max_onTime = 5.0f;
	float onTime = Max_onTime;
};