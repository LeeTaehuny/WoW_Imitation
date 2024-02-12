#pragma once
class P_010_Moment_Of_Glory : public ActiveSkill
{
public:
	P_010_Moment_Of_Glory();
	~P_010_Moment_Of_Glory();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(CH_Base_ver2* chbase) override;

private:
	float NujecDamage = 0;

	// ��ų�� ���۵ǰ� ���� ���� �ð��� üũ�ϱ� ���� ��Ÿ��
	float maxRuntime = 15.0f;
	float curRuntime = maxRuntime;

	CH_Base_ver2* targetCharcter;
};