#pragma once
class P_014_Blessing_of_Spellwarding : public ActiveSkill
{
public:
	P_014_Blessing_of_Spellwarding();
	~P_014_Blessing_of_Spellwarding();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() {}
	virtual void UseSkill(Collider* targetCollider) override;
	virtual void UseSkill(Vector3 direction) {}

private:
	// 캐릭터의 데이터를 받아오기 위한 변수
	CH_Base_ver2* characterData;

	// 나중에 이펙트 추가 필요
	// 파티클시스템을 통해 위로 날아가는 듯한 파티클
	ParticleSystem* particle;

	//

};