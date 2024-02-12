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

	// 스킬이 시작되고 나서 지난 시간을 체크하기 위한 쿨타임
	float maxRuntime = 15.0f;
	float curRuntime = maxRuntime;

	CH_Base_ver2* targetCharcter;
};