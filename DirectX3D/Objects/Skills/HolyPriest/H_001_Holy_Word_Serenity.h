#pragma once
class H_001_Holy_Word_Serenity : public ActiveSkill
{
public:
	H_001_Holy_Word_Serenity();
	~H_001_Holy_Word_Serenity();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase) override;

private:
	// 파티클 이펙트
	ParticleSystem* particle;
	int isOne = 0;

	// 힐 수치를 적용할 대상 캐릭터의 정보를 저장하기 위한 변수
	CH_Base_ver2* healingTarget;
};