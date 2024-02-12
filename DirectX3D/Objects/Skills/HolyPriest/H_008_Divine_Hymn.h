#pragma once
class H_008_Divine_Hymn : public ActiveSkill
{
public:
	H_008_Divine_Hymn();
	~H_008_Divine_Hymn();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() override;

private:
	ParticleSystem* particle1;
	ParticleSystem* particle2;
	float startTimeDelay = 0;

	float Max_tickTime = 1;
	float tickTime = Max_tickTime;

	float Max_animStart = 0.9f;
	float animStart = 0;
};