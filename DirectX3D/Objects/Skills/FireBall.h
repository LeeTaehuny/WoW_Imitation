#pragma once
class FireBall : public TargetSkill
{
public:
	FireBall();
	~FireBall();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(Vector3 pos) override;

private:

};