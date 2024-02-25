#pragma once
class Lich_005_Remorseless_Winter : public Lich_000_Base
{
public:
	Lich_005_Remorseless_Winter(Boss_LichKing* lich);
	~Lich_005_Remorseless_Winter();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase = nullptr) override;

	bool GetSkillEnd() { return skillend; }
	void ChangeSkillEnd() { skillend = !skillend; }

private:
	ParticleSystem* particle;
	Collider* hitCollider;

	// 0.5�ʸ��� �������� �ְ��ϱ� ���� ����
	float Max_tickTime = 0.5f;
	float tickTime = Max_tickTime;

	bool skillend = false;

	// 60�ʸ� �۵��ϵ��� �ϰ��ϱ� ���� ����
	float Max_runTime = 60.0f;
	float runTime = Max_runTime;
};