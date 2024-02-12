#pragma once
class H_002_Holy_Word_Sanctify : public ActiveSkill
{
public:
	H_002_Holy_Word_Sanctify();
	~H_002_Holy_Word_Sanctify();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

private:
	// 파티클의 정보를 저장하기 위한 벡터 (사이즈는 5개 고정)
	vector<ParticleSystem*> particles;
	vector<int> isOne;

	// 회복할 캐릭터의 정보를 저장하기 위한 벡터 (사이즈는 5개 고정
	vector<CH_Base_ver2*> healingTargets;

	float Max_animStart = 0.9f;
	float animStart = 0;
};